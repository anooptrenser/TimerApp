cmake_minimum_required(VERSION 3.10) 
project(TimerApp C)

set(CMAKE_C_STANDARD 17)
set(SRC main.c appTimer/appTimer.c simulateLED/simulateLED.c)

# Release build
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

# Debug build
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