#!/bin/bash

# pico-sdk deps
pkg_MANAGER=pkg

if command -v apt > /dev/null; then
    pkg_MANAGER=apt
elif command -v dnf > /dev/null; then
    pkg_MANAGER=dnf
elif command -v yum > /dev/null; then
    pkg_MANAGER=yum
else
    .
fi

$pkg_MANAGER list installed cmake python3 build-essential gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib || sudo $pkg_MANAGER install cmake python3 build-essential gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib gcc-arm-none-eabi

# pico-sdk
if [ -d "pico-sdk/" ]; then
    cp pico-sdk/external/pico_sdk_import.cmake pico_sdk_import.cmake
    echo "pico-sdk is on dir."
else

wget "https://github.com/raspberrypi/pico-sdk/blob/master/external/pico_sdk_import.cmake"

picosdk_VERSION=2.2.0
wget -O "picoSDK.tar.gz" "https://github.com/raspberrypi/pico-sdk/releases/download/$picosdk_VERSION/pico-sdk-$picosdk_VERSION.tar.gz"

# decompress
tar -xf "picoSDK.tar.gz"
rm "picoSDK.tar.gz"
mv "pico-sdk-$picosdk_VERSION" "pico-sdk"
cp pico-sdk/external/pico_sdk_import.cmake pico_sdk_import.cmake
fi
