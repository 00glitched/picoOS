#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*hal_timer_cb_t)(void);

void hal_timer_init(uint32_t tick_us, hal_timer_cb_t cb);

#endif
