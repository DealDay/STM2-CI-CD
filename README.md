# STM2-CI-CD
This project shows how to utilise CI/CD pipeline to compile, test and deploy embedded software for an ST microcontroller. STM32L475VGT6 was used for this project. This project can be used, with little edit, to flash any STM32L475VGTx. For more information on the project setup/pipeline please read Appendix C & D of Embedded Software Design a Practical Architecture Processes and Coding by Jacob Beningo
## Usage
### Prerequisite
1. [git installed](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) 
2. docker installed
    - For Mac: start here https://docs.docker.com/desktop/mac/install/
    - For Windows: start here https://docs.docker.com/desktop/windows/install/
    - For Linux: search for instructions for your system.
### Clone repository
cd \<to-desired-directory>
######
        git clone https://github.com/DealDay/STM2-CI-CD.git
### Pull dealday/gcc-arm:latest from docker hub
        docker pull dealday/gcc-arm:latest
### Run docker image
cd \<repository-location>
        docker run --rm -it --privileged -v "$(PWD):/home/app" dealday/gcc-arm:latest bash
### Change to project directory
        cd myProject
### Build project
        make all
### Delete build directory
        make clean
### Run test
        make test
For more information on how to use the unit test please visit https://github.com/jwgrenning/cpputest-starter-project
### Delete test folders
        make clean_test
### Deploy to target
        make deployToTarget
You can delete files in Firmware/Application and add your customised code there
