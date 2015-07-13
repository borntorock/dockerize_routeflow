#include <sys/ioctl.h>
#include <netpacket/packet.h>
#include <syslog.h>
#include <cstdio>
#include <boost/bind.hpp>

#include "defs.h"
#include "PortMapper.hh"

#define BUFFER_SIZE 23 /* Mapping packet size. */
#define SLEEP_TIME boost::posix_time::seconds(10)

PortMapper::PortMapper(uint64_t vm_id, map<int, Interface*> *ifaces, boost::mutex *ifMutex) {
    this->id = vm_id;
    this->ifaces = ifaces;
    this->ifMutex = ifMutex;
}

/**
 * Loops through interfaces, sending mapping packets out each, then sleeps.
 * Rinse and repeat ad infinitum.
 */
void PortMapper::operator()() {
    while(true) {
        boost::system_time timeout = boost::get_system_time() + SLEEP_TIME;

        /* Grab list of interfaces from RFClient, iterate, send map packet */
        {
            boost::lock_guard<boost::mutex> lock(*(this->ifMutex));
            map<int, Interface*>::iterator it;
            for (it = this->ifaces->begin(); it != this->ifaces->end(); it++) {
                Interface &iface = *(it->second);
                if (iface.physical && !iface.active) {
                    this->send_port_map(iface);
                }
            }
        }

        boost::this_thread::sleep(timeout);
    }
}

/**
 * Sends a portmap packet out the given interface, logging the success or
 * failure of the endeavour.
 */
void PortMapper::send_port_map(Interface &iface) {
    if (send_packet(iface.name.c_str(), iface.port) == -1)
        syslog(LOG_NOTICE, "Error sending mapping packet via %s",
               iface.name.c_str());
    else
        syslog(LOG_DEBUG, "Mapping packet was sent to RFVS via %s",
               iface.name.c_str());
}

/**
 * Sends the magic RouteFlow portmap packet out an interface with the given
 * name, encoding the given port number inside the message.
 *
 * Returns the number of characters sent, or -1 on failure.
 */
int PortMapper::send_packet(const char ethName[], uint8_t port) {
    char msg[BUFFER_SIZE];
    char buffer[BUFSIZ];
    uint16_t ethType;
    struct ifreq req;
    struct sockaddr_ll sll;
    uint8_t srcAddress[IFHWADDRLEN];
    uint8_t dstAddress[IFHWADDRLEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    int ifindex, addrLen, SockFd;
    int error = -1;

    SockFd = socket(PF_PACKET, SOCK_RAW, htons(RF_ETH_PROTO));

    memset(&req, 0, sizeof(req));
    strcpy(req.ifr_name, ethName);
    if (ioctl(SockFd, SIOCGIFFLAGS, &req) < 0) {
        goto exit;
    }

    /* If the interface is down we can't send the packet. */
    if (!(req.ifr_flags & IFF_UP)) {
        goto exit;
    }

    /* Get the interface index. */
    if (ioctl(SockFd, SIOCGIFINDEX, &req) < 0) {
        goto exit;
    }

    /* Get the MAC address. */
    ifindex = req.ifr_ifindex;
    if (ioctl(SockFd, SIOCGIFHWADDR, &req) < 0) {
        goto exit;
    }
    memcpy(srcAddress, req.ifr_hwaddr.sa_data, IFHWADDRLEN);

    /* Bind to the socket. */
    memset(&sll, 0, sizeof(struct sockaddr_ll));
    sll.sll_family = PF_PACKET;
    sll.sll_ifindex = ifindex;
    addrLen = sizeof(sll);
    if (bind(SockFd, (struct sockaddr *) &sll, addrLen) < 0) {
        goto exit;
    }

    /* Construct the packet and send it. */
    memset(msg, 0, BUFFER_SIZE);
    memcpy((void *) msg, (void *) dstAddress, IFHWADDRLEN);
    memcpy((void *) (msg + IFHWADDRLEN), (void *) srcAddress, IFHWADDRLEN);
    ethType = htons(RF_ETH_PROTO);
    memcpy((void *) (msg + 2 * IFHWADDRLEN), (void *) &ethType,
            sizeof(uint16_t));
    memcpy((void *) (msg + 14), (void *) &this->id, sizeof(uint64_t));
    memcpy((void *) (msg + 22), (void *) &port, sizeof(uint8_t));
    error = (sendto(SockFd, msg, BUFFER_SIZE, 0, (struct sockaddr *) &sll,
             (socklen_t) addrLen));

exit:
    if (error <= 0) {
        strerror_r(errno, buffer, BUFSIZ);
        syslog(LOG_ERR, "send_packet(): %s", buffer);
    }
    close(SockFd);
    return error;
}
