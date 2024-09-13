FROM ubuntu:latest
# ENV REFRESHED_AT=2024-08-26
# Download Linux support tools
RUN apt-get update && apt-get clean && \
    apt-get install -y build-essential wget curl git && \
    apt-get install -y autoconf libtool

# Download and install JLink tools
RUN wget --post-data 'accept_license_agreement=accepted' https://www.segger.com/downloads/jlink/JLink_Linux_V798h_x86_64.deb \
    && DEBIAN_FRONTEND=noninteractive TZ=America/Los_Angeles \
    && apt-get install -y libxcb-render-util0-dev libxrender1 libxcb-shape0 libxcb-randr0 libxcb-xfixes0 libxcb-sync1 \
    libxcb-shm0 libxcb-icccm4 libxcb-keysyms1 libxcb-image0 libxkbcommon0 libxkbcommon-x11-0 libx11-xcb1 libsm6 \
    libice6 libglib2.0-0 \
    && echo '#!/bin/bash\necho not running udevadm "$@"' > /usr/bin/udevadm && chmod +x /usr/bin/udevadm \
    && dpkg -i ./JLink_Linux_V798h_x86_64.deb \
    && rm JLink_Linux_V798h_x86_64.deb
ENV PATH=$PATH:/opt/SEGGER/JLink

# Install and configure CppUTest
WORKDIR /home/cpputest
RUN git clone --depth 1 --branch v4.0 https://github.com/cpputest/cpputest.git .
RUN autoreconf . -i
RUN ./configure
RUN make install
ENV CPPUTEST_HOME=/home/cpputest

# Set up a development tools directory
WORKDIR /home/dev
ADD . /home/dev
RUN wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 | tar -xj
# Set up the compiler path
ENV PATH=$PATH:/home/dev/gcc-arm-none-eabi-10.3-2021.10/bin
WORKDIR /home/app
