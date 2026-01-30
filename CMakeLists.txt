cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/pico-sdk)

include(${CMAKE_CURRENT_LIST_DIR}/pico_sdk_import.cmake)

project(nanokernel C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(nanokernel
    main.c

    kernel/kernel.c
    kernel/scheduler.c

    hal/hal.c
    hal/hal_gpio.c
    hal/hal_uart.c
    hal/hal_timer.c

    drivers/led.c
    bin/blink.c
)

target_include_directories(pico_os PRIVATE
    .
    include
    kernel
    hal
    drivers
)

target_link_libraries(pico_os pico_stdlib hardware_timer hardware_uart)

pico_add_extra_outputs(pico_os)
