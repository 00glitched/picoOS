#include "hal_uart.h"
#include "pico/stdlib.h"
#include <stdio.h>

void hal_uart_init(void) {
    stdio_init_all();
}

void hal_uart_write(const char *s) {
    printf("%s", s);
}

void hal_uart_write_n(const char *s, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        putchar_raw(s[i]);
    }
}
