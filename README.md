# TimerApp

A cross-platform C project that builds a timer application for both Linux and Raspberry Pi, using either **CMake** or **Make** as the build system.

## Features

- Organized source code in multiple directories
- Separate **release** and **debug** builds
- Cross-compilation support for Raspberry Pi (aarch64)
- Clean, portable build system

## Prerequisites

- **CMake** ≥ 3.10
- **Make**
- **GCC** (for Linux build)
- **aarch64-linux-gnu-gcc** (for Raspberry Pi cross-compilation)


## Building with Make

## Build release executable for host
make linux

## Build debug executable for host
make debug

##Cross-compile for Raspberry Pi (no GPIO)
make rpi

## Cross-compile for Raspberry Pi with GPIO support
make rpi-led

## Build all targets
make all

##Clean build artifacts
make clean


## Building with CMake

### 1. Release Build

$ mkdir build && cd build
$ cmake ..
$ make
$ mkdir build
$ cmake ..
$ make

## Execution of Sanity Check
Place sanityCheck.sh in the project root (same directory as the Makefile).
$chmod +x sanityCheck.sh
./sanityCheck.sh

On completion report.txt file will be generated.






