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

### 1. Linux (Release)

$ make linux

- Output: `release/appTimerexecutable`

### 2. Linux (Debug)

$ make linux-debug

- Output: `debug/appTimerexecutable`

### 3. Raspberry Pi (Release, cross-compile)

$ make rpi

- Output: `release/appTimerexecutable_rpi`

### 4. Raspberry Pi (Debug, cross-compile)

$ make rpi-debug

- Output: `debug/appTimerexecutable_rpi`

### 5. Build All

$ make all

- Builds both Linux and Raspberry Pi release targets.

### 6. Clean Build Artifacts

$ make clean

- Removes all files from `release/` and `debug/` folders.

## Building with CMake

### 1. Release Build

$ mkdir build && cd build
$ cmake ..
$ make
$ mkdir build
$ cmake ..
$ make






