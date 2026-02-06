#!/bin/bash
LPATH=$(pwd)
WHO=$(whoami)
cp $LPATH/build/pico_os.uf2 /media/$WHO/RPI-RP2/pico_os.uf2
