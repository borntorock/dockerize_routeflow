#!/bin/bash

MONGODB_ADDR="192.168.10.1"

sleep 5
/etc/rfclient/rfclient -a $MONGODB_ADDR 2>&1 /var/log/rfclient.log
