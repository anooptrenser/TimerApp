# Toolchain file for Raspberry Pi (aarch64) cross-compilation

# Specify the target system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Specify the cross compilers
# Assuming these are in your system's PATH
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++) # Even if only C is used, good practice

# Specify the search path for programs and libraries
# NEVER search for programs in the sysroot (we want host programs like cmake, make)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# ALWAYS search for libraries and includes ONLY in the sysroot
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

