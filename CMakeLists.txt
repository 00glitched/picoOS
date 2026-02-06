cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/pico-sdk)

include(${CMAKE_CURRENT_LIST_DIR}/pico_sdk_import.cmake)

project(pico_os C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(pico_os
    main.c

    core/kernel/kernel.c
    kernel/scheduler.c

    core/hal/hal.c
    core/hal/hal_gpio.c
    core/hal/hal_uart.c
    core/hal/hal_timer.c

    core/drivers/led.c
    core/bin/blink.c
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
