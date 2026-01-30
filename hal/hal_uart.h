#pragma once
#include <stdint.h>

void hal_uart_init(void);
void hal_uart_write(const char *s);
void hal_uart_write_n(const char *s, uint32_t len);
