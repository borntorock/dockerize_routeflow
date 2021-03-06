# Dockerize RouteFlow

The goal of this project is to build the RouteFlow along with its virtual plane components inside the docker containers. 

# Building

> If you want to build RouteFlow along with its virtual plane components inside the docker containers, follow the steps mentioned below:

1. Create Docker image with Ubuntu 14.04 and the dependencies (used for building RouteFlow) installed.
```
sudo docker build --tag routeflow/routeflowx:v1 .
```

2. Launch Docker container for building RouteFlow from routeflowx:v1 docker image
```
sudo docker run -d --name="routeflow" routeflow/routeflowx:v1
```

Now, with the above steps, you have setup the RouteFlow inside the docker container. 
You are now ready to run the tests 1 and 2. For running the tests, refer the "Running" section.


# Installation
Once the RouteFlow docker container is up and running, you have all the packages (required for building RouteFlow) installed in the RouteFlow docker image using build.sh script except Open vSwitch.

You need to manually install Open vSwitch after login to the RouteFlow docker container. 
```
$ sudo apt-get install openvswitch-switch openvswitch-common openvswitch-datapath-source
```


# Running

The folder rftest contains all that is needed to create and run two test cases.

## Virtual environment

First, create the docker containers for the RouteFlow virtual plane components that will run as virtual machines:
```
$ cd rftest
$ sudo ./create_docker
```

## Test scenarios

Default configuration files and Dockerfiles are present in the `rftest` directory.
You can stop the test at any time by pressing CTRL+C.

### rftest1

1. Run:
```
$ sudo ./rftest1_docker -z --ryu
```

2. You can then log in to the b1 docker container and try to ping b2:
```
$ sudo docker exec -it b1 bash
```

3. Inside b1 docker container, run:
```
# ping 172.31.2.2
```

### rftest2
This test should be run with a [Mininet](http://mininet.org/) simulated network.
In the steps below, replace [guest address] with the IP address you use to access your Mininet VM.
The same applies to [host address], that should be the address to access the host from inside the VM.

1. Run:
```
$ sudo ./rftest2
```

2. Once you have a Mininet VM up and running, copy the network topology files in rftest to the VM:
```
$ scp topo-4sw-4host.py mininet@[guest address]:/home/mininet/mininet/custom
$ scp ipconf mininet@[guest address]:/home/mininet
```

3. Then start the network:
```
$ sudo mn --custom mininet/custom/topo-4sw-4host.py --topo=rftest2 --controller=remote,ip=[host address],port=6633 --pre=ipconf
```

Wait for the network to converge (it should take a few seconds), and try to ping:
```
mininet> pingall
...
mininet> h2 ping h3
```


# Support
If you want to know more or need to contact us regarding the project for anything (questions, suggestions, bug reports, discussions about RouteFlow and SDN in general), you can contact via our Google Groups [mailing list](http://groups.google.com/group/routeflow-discuss?hl=en_US)

