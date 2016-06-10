## Prerequisites
* arm gcc
* st-util or openocd
* make / cygwin
* STM32CubeF7 firmware library

## Setup
* unzip STM32Cube_FW_F7 into Libraries directory
* edit common.mk to set TOOLROOT to arm gcc installation path

## Build
* make clean - remove output and intermediary files
* make all - build binary
* make debug - connect a remote gdb session on port 4242
