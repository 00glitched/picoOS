#include "hal_uart.h"
#include "pico/stdlib.h"
#include <stdio.h>

void hal_uart_init(void) {
    stdio_init_all();
}

void hal_uart_write(const char *s) {
    printf("%s", s);
}

void hal_uart_write_str(const char *s) {
    hal_uart_write(s);
}

void hal_uart_write_n(const char *s, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        putchar_raw(s[i]);
    }
}

int hal_uart_getc(void) {
    int c = getchar_timeout_us(0);   // no bloqueante (0us)
    return c;                       // -1 si no hay dato
}
