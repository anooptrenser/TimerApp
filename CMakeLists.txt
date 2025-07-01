cmake_minimum_required(VERSION 3.10)
project(TimerApp C)
set(CMAKE_C_STANDARD 17)

set(SRC
    main.c
    appTimer/appTimer.c
    simulateLED/simulateLED.c
)

add_executable(TimerApp ${SRC})

target_include_directories(TimerApp PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/appTimer
    ${CMAKE_SOURCE_DIR}/simulateLED
)

target_compile_options(TimerApp PRIVATE -Wall -Wextra)

# Set output directory based on build type
set_target_properties(TimerApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}
)
