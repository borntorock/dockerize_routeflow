# Dockerize RouteFlow
The goal of this is to build the RouteFlow along with its virtual plane components inside the docker containers. 


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




# Support
If you want to know more or need to contact us regarding the project for anything (questions, suggestions, bug reports, discussions about RouteFlow and SDN in general), you can contact via our Google Groups [mailing list](http://groups.google.com/group/routeflow-discuss?hl=en_US)

