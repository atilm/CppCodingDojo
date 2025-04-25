ARG IMAGE=ubuntu:24.04

FROM ${IMAGE}

RUN apt-get -y update && \
    apt-get -y install git cmake python3 python-is-python3 build-essential g++-12 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 100 && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100

