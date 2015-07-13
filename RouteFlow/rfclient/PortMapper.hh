#ifndef PORTMAPPER_H
#define PORTMAPPER_H

#include <vector>
#include <boost/thread.hpp>
#include "Interface.hh"

class PortMapper {
    public:
        PortMapper(uint64_t vm_id, map<int, Interface*> *ifaces, boost::mutex *ifMutex);
        void operator()();

    private:
        uint64_t id;
        map<int, Interface*> *ifaces;
        boost::mutex *ifMutex;

        void send_port_map(Interface &iface);
        int send_packet(const char ethName[], uint8_t port);
};

#endif /* PORTMAPPER_H */
