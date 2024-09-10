# STM2-CI-CD
This project shows how to utilise CI/CD pipeline to compile and test embedded software for an STM32 microcontroller. 
## Usage
### Prerequisite
1. [git installed](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) 
2. docker installed
    - For Mac: start here https://docs.docker.com/desktop/mac/install/
    - For Windows: start here https://docs.docker.com/desktop/windows/install/
    - For Linux: search for instructions for your system.
### Clone repository
cd '<to-desired-directory>'
######
        git clone https://github.com/DealDay/STM2-CI-CD.git
### Pull dealday/gcc-arm:latest from docker hub
        docker pull dealday/gcc-arm:latest
### Run docker image
cd \<repository-location>
######
        docker run --rm -it --privileged -v "$(PWD):/home/app" adeola/gcc-arm:latest bash

