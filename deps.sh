#!/bin/bash

# pico-sdk deps
pkg_MANAGER=dnf
$pkg_MANAGER list installed cmake python3 build-essential gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib || sudo $pkg_MANAGER install cmake python3 build-essential gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib

# pico-sdk
if [ -d "pico-sdk/" ]; then
    echo " pico-sdk is on dir."
else

wget "https://github.com/raspberrypi/pico-sdk/blob/master/external/pico_sdk_import.cmake"

picosdk_VERSION=2.2.0
wget -O "picoSDK.tar.gz" "https://github.com/raspberrypi/pico-sdk/releases/download/$picosdk_VERSION/pico-sdk-$picosdk_VERSION.tar.gz"

# decompress
tar -xf "picoSDK.tar.gz"
rm "picoSDK.tar.gz"
mv "pico-sdk-$picosdk_VERSION" "pico-sdk"
fi
