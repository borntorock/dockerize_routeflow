#!/bin/bash

sleep 5
/etc/init.d/quagga start
/etc/rfclient/rfclient 2&>1 /var/log/rfclient.log
