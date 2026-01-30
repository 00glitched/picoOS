#include "hal.h"
#include "hal_uart.h"
#include "hal_timer.h"

void hal_init(void) {
    hal_uart_init();
    //hal_timer_init();
}
