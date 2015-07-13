#!/usr/bin/python

from mininet.net import Mininet
from mininet.node import Controller, RemoteController, OVSController
from mininet.node import CPULimitedHost, Host, Node
from mininet.node import OVSKernelSwitch, UserSwitch
from mininet.node import IVSSwitch
from mininet.cli import CLI
from mininet.log import setLogLevel, info
from mininet.link import TCLink, Intf
import time
import sys

def myNetwork():

    net = Mininet( topo=None,
                   build=False,
                   ipBase='10.0.0.0/8')

    info('*** Adding controller\n' )
    c0 = net.addController( name='c0',
                            controller=RemoteController,
                            ip='127.0.0.1',
                            port=6633)

    info('*** Add switches\n')
    s153 = net.addSwitch('s153', cls=OVSKernelSwitch)

    info('*** Add hosts\n')
    h2 = net.addHost('h2', cls=Host, ip='172.31.2.2/24', defaultRoute="via 172.31.2.1")
    h1 = net.addHost('h1', cls=Host, ip='172.31.1.2/24', defaultRoute="via 172.31.1.1")

    info('*** Add links\n')
    net.addLink(h1, s153)
    net.addLink(s153, h2)

    info('*** Starting network\n')
    net.build()
    info('*** Starting controllers\n')
    for controller in net.controllers:
        controller.start()

    info('*** Starting switches\n')
    net.get('s153').start([c0])

    info('*** Configuring switches\n')
    # wait for configuration to complete
    #TODO: if the flowtable gets changed then the number of flows
    # here may be too high
    while True:
        flowtable = s153.cmd("ovs-ofctl -O OpenFlow13 dump-flows s153")
        if (len(flowtable.splitlines()) > 20):
            break
        time.sleep(2)

    info('*** Performing tests\n')
    info('*** Testing connectivity between h1 and rfvm\n')
    h1.cmdPrint("ping -c 1 172.31.1.1")
    ping =  h1.popen("ping -c 1 172.31.1.1")
    ping.wait()
    if ping.returncode != 0:
        sys.exit(1)
    info('*** Testing connectivity between h2 and rfvm\n')
    h2.cmdPrint("ping -c 1 172.31.2.1")
    ping =  h2.popen("ping -c 1 172.31.2.1")
    ping.wait()
    if ping.returncode != 0:
        sys.exit(1)
    info('*** Testing connectivity between h1 and h2\n')
    h1.cmdPrint("ping -c 1 172.31.2.2")
    ping =  h1.popen("ping -c 1 172.31.2.2")
    ping.wait()
    if ping.returncode != 0:
        sys.exit(1)
    info('*** Connectivity test successful\n')
    net.stop()

if __name__ == '__main__':
    setLogLevel('info' )
    myNetwork()
