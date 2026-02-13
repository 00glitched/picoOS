cmake_minimum_required(VERSION 3.13)
project(picoOS C ASM)

set(CMAKE_C_STANDARD 11)

add_executable(picoOS
    src/main.c
)
include(pico_sdk_import.cmake)
pico_sdk_init()

target_link_libraries(picoOS pico_stdlib)
