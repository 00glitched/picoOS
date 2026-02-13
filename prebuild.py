#!/usr/bin/env python3
from pathlib import Path

MAIN_C = """\
#include "core/include/nkernel.h"

// tasks
extern void blink_task(void);
extern void term_task(void);

int main(void)
{
    kernel_init();

    task_create(blink_task, 512);
    task_create(term_task, 512);

    scheduler_start();

    while (1); // infinite loop
}
"""


CORE_H = """\
// hardware
#define CFG_CORES {cores}
#define CFG_FLASH {flash}
#define CFG_TICKUS {tick}
#define CFG_MAXTASK {tasks}


// core-bin activation
#define CFG_BIN_TERM {term}
#define CFG_BIN_MEM  {mem}
#define CFG_BIN_FILE {file}
#define CFG_BIN_TASK {task}


// core-bin config

// term
#define CFG_BIN_TERM_MAXCHAR {term_char}
#define CFG_BAUDRATE {baud}


// mem
#define CFG_BIN_MEM_MSGAT {mem_msg}
"""


CMAKE = """\
cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${{CMAKE_CURRENT_LIST_DIR}}/pico-sdk)

include(${{CMAKE_CURRENT_LIST_DIR}}/pico_sdk_import.cmake)

project({name} C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

file(GLOB_RECURSE CORE_SRC
    core/kernel/*.c
    core/hal/*.c
    core/drv/*.c
    core/bin/*.c
)

add_executable({name}
    main.c
    ${{CORE_SRC}}
)

target_include_directories({name} PRIVATE
    .
    include
    kernel
    hal
    drv
)

target_link_libraries({name}
    pico_stdlib
    hardware_timer
    hardware_uart
)

pico_enable_stdio_usb({name} 1)
pico_enable_stdio_uart({name} 1)

pico_add_extra_outputs({name})
"""

def ask(msg, default):
    v = input(f"{msg} [{default}]: ").strip()
    return v if v else default


def ask_bool(msg, default=True):
    d = "y" if default else "n"
    v = input(f"{msg} (y/n) [{d}]: ").lower().strip()
    if not v:
        return default
    return v == "y"


def write(path: Path, content: str):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content)
    print(f"[+] {path}")


def main():

    print("\npicoOS prebuild\n")

    name = ask("Project name", "pico_os")

    cores = ask("CORES", 1)
    flash = ask("FLASH (kB)", 64)
    tick  = ask("TICK (us)", 1000)
    tasks = ask("MAX TASKS", 8)

    print("\n-- bins --")
    term = int(ask_bool("Enable TERM", True))
    mem  = int(ask_bool("Enable MEM", True))
    file = int(ask_bool("Enable FILE", True))
    task = int(ask_bool("Enable TASK", True))
    task = int(ask_bool("Enable VAR", True))


    print("\n-- configs --")
    term_char = ask("TERM max chars", 32)
    baud      = ask("UART baudrate", 9600)
    mem_msg   = ask("MEM warn threshold (KB)", 123)

    #root = Path(name)

    write("main.c", MAIN_C)

    write("cfg/core.h",
          CORE_H.format(
              cores=cores,
              flash=flash,
              tick=tick,
              tasks=tasks,
              term=term,
              mem=mem,
              file=file,
              task=task,
              term_char=term_char,
              baud=baud,
              mem_msg=mem_msg
          ))

    write("CMakeLists.txt",
          CMAKE.format(name=name))

    print("\n✔ Config.")


if __name__ == "__main__":
    main()
