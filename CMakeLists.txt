cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/pico-sdk)

include(${CMAKE_CURRENT_LIST_DIR}/pico_sdk_import.cmake)

project(pico_os C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

file(GLOB_RECURSE CORE_SRC
    core/kernel/*.c
    core/hal/*.c
    core/drv/*.c
    core/bin/*.c
)

add_executable(pico_os
    main.c
    ${CORE_SRC}
)

target_include_directories(pico_os PRIVATE
    .
    include
    kernel
    hal
    drv
)

target_link_libraries(pico_os pico_stdlib hardware_timer hardware_uart)

pico_enable_stdio_usb(pico_os 1)
pico_enable_stdio_uart(pico_os 1)

pico_add_extra_outputs(pico_os)
