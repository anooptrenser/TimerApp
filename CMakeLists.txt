cmake_minimum_required(VERSION 3.10)
project(TimerApp C)

set(CMAKE_C_STANDARD 17)
set(SRC main.c appTimer/appTimer.c simulateLED/simulateLED.c)

# Option to enable Raspberry Pi cross-compilation
option(BUILD_FOR_RASPBERRY_PI "Build for Raspberry Pi (cross-compilation)" OFF)

# Check if we are cross-compiling for Raspberry Pi
if(BUILD_FOR_RASPBERRY_PI)
    message(STATUS "Configuring for Raspberry Pi cross-compilation.")
else()
    message(STATUS "Configuring for native build.")
endif()

# Native Builds (for your host Linux machine)
# These will still output to 'release' and 'debug' subdirectories directly under the source dir
# if built natively.
add_executable(TimerApp ${SRC})
target_include_directories(TimerApp PRIVATE
    ${CMAKE_SOURCE_DIR}/
    ${CMAKE_SOURCE_DIR}/appTimer/
    ${CMAKE_SOURCE_DIR}/simulateLED/
)
target_compile_options(TimerApp PRIVATE -Wall -Wextra)
set_target_properties(TimerApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/release
)

add_executable(TimerApp_debug ${SRC})
target_include_directories(TimerApp_debug PRIVATE
    ${CMAKE_SOURCE_DIR}/
    ${CMAKE_SOURCE_DIR}/appTimer/
    ${CMAKE_SOURCE_DIR}/simulateLED/
)
target_compile_options(TimerApp_debug PRIVATE -Wall -Wextra -g)
set_target_properties(TimerApp_debug PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/debug
)

# Raspberry Pi Cross-Compilation Target (Flexible Debug/Release)
if(BUILD_FOR_RASPBERRY_PI)
    add_executable(TimerApp_raspi ${SRC})
    target_include_directories(TimerApp_raspi PRIVATE
        ${CMAKE_SOURCE_DIR}/
        ${CMAKE_SOURCE_DIR}/appTimer/
        ${CMAKE_SOURCE_DIR}/simulateLED/
    )
    # Use generator expressions to apply different flags based on CMAKE_BUILD_TYPE
    target_compile_options(TimerApp_raspi PRIVATE -Wall -Wextra
        # Debug configuration: include debug symbols, no optimization
        $<$<CONFIG:Debug>:-g>
        # Release with Debug Info: include debug symbols, moderate optimization
        $<$<CONFIG:RelWithDebInfo>:-g -O2>
        # Minimum Size Release: optimize for size, no debug info
        $<$<CONFIG:MinSizeRel>:-Os -DNDEBUG>
        # Release configuration: aggressive optimization, no debug info, disable asserts
        $<$<CONFIG:Release>:-O3 -DNDEBUG>
    )
    # Set output directory to include the build type (e.g., raspi_build/Debug, raspi_build/Release)
    set_target_properties(TimerApp_raspi PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/raspi_build/$<CONFIG>
    )
endif()
