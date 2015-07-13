#!/bin/sh

ZMQ_URL="http://download.zeromq.org/"
ZMQ_GIT="git@github.com:zeromq/libzmq.git"
ZMQ_BRANCH="master"

##
# Fetch and build MongoDB from source.
#
# $1 - Version string or "git"
##
build_zmq() {
    if [ -e "zeromq-$1" ] && [ $UPDATE -eq 0 ]; then
        return;
    fi

    fetch "zeromq-" $1 $ZMQ_GIT $ZMQ_BRANCH $ZMQ_URL ||
        fail "Couldn't fetch MongoDB"

    if [ $FETCH_ONLY -ne 1 ]; then
        $SUPER pip install pyzmq==13.1.0

        $DO ./configure || fail "Couldn't configure ZeroMQ"
        $DO make || fail "Couldn't build ZeroMQ"
        $SUPER make install || fail "Couldn't install ZeroMQ"
        $SUPER ldconfig
        $DO cd ..
    fi
}

get_zmq() {
    build_zmq $@
}
