#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdint.h>

void hal_uart_init(void);

void hal_uart_write(const char *s);
void hal_uart_write_n(const char *s, uint32_t len);

int  hal_uart_getc(void);          // no bloqueante
void hal_uart_write_str(const char *s); // alias cómodo

#endif
