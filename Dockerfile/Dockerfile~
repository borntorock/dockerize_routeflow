# Dockerfile for building RouteFlow

# Pulling base image
FROM ubuntu:14.04

# Maintainer
MAINTAINER Nitin Agarwal nitinagarwal3006@gmail.com

# Updating and Installing packages 
RUN apt-get update && \
    apt-get install -y build-essential \
                       pkg-config \
                       git-core \
                       libboost-dev \
                       libboost-program-options-dev 
                       libboost-thread-dev \
                       libboost-filesystem-dev \
                       libboost-system-dev \
                       libnl-3-dev \
                       libnl-route-3-dev \
                       python-dev \
                       python-pip \
                       python-bson

# Installing Pipework inside the RouteFlow container
ADD https://github.com/jpetazzo/pipework/blob/master/pipework /usr/sbin/pipework
RUN chmod +x /usr/sbin/pipework

# Cloning of the RouteFlow repository in "/var" directory
RUN git clone https://github.com/routeflow/RouteFlow.git /var

# Building the RouteFlow from the build script
RUN chmod +x /var/RouteFlow/build.sh

ENTRYPOINT ["/var/RouteFlow/build.sh", "-c", "-z", "ryu"]
