# Dockerfile for building rfvmX containers

# Pulling base image
FROM ubuntu:14.04

# Maintainer
MAINTAINER RouteFlow routeflow-discuss@googlegroups.com

# Installing packages 
RUN apt-get update && \
    apt-get install -y libboost-thread-dev \
                       libboost-system-dev \
                       libboost-filesystem-dev \
                       libboost-program-options-dev \
                       libnl-3-dev \
                       libnl-route-3-dev \
                       quagga \
                       rsyslog \
                       tcpdump \
                       vlan 

# COPYing daemons and debian config files in /etc/quagga folder
#COPY quagga/daemons /etc/quagga/daemons
#COPY quagga/debian.conf /etc/quagga/debian.conf

# COPYing sysctl config file in /etc folder
#COPY sysctl.conf /etc/sysctl.conf

# COPYing run_rfclient.sh script and providing it executable permissions
COPY run_rfclient.sh /usr/sbin/run_rfclient.sh
RUN chmod +x /usr/sbin/run_rfclient.sh

# Creating the rfclient dir and copying the rfclient executable
RUN mkdir /etc/rfclient

COPY libzmq.so /usr/lib/libzmq.so

RUN ldconfig

COPY rfclient /etc/rfclient/rfclient

ENTRYPOINT ["/usr/sbin/run_rfclient.sh"]
