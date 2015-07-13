# Dockerfile for building rfvm1 container

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
                       rsyslog \
                       vlan \
                       tcpdump

# COPYing the daemons and debian config file in the /etc/quagga folder
#COPY quagga/daemons /etc/quagga/daemons
#COPY quagga/debian.conf /etc/quagga/debian.conf

# COPYing the sysctl.conf file in the /etc folder
#COPY sysctl.conf /etc/sysctl.conf

# COPYing the run_rfclient.sh script file and providing it executable permissions
COPY run_rfclient.sh /usr/sbin/run_rfclient.sh
RUN chmod +x /usr/sbin/run_rfclient.sh

# Creating the rfclient dir and copying the rfclient executable from the build folder to the /etc/rfclient folder
RUN mkdir /etc/rfclient
COPY rfclient /etc/rfclient/rfclient

COPY libzmq.so /usr/lib/libzmq.so

RUN ldconfig

ENTRYPOINT ["/usr/sbin/run_rfclient.sh"]
