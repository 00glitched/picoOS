#include "pico/stdlib.h"
#include "hal/hal.h"
#include "bin/blink.h"

int main(void) {
    stdio_init_all();
    hal_init();

    blink_test();

    while (1) { }
}
