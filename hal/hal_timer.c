#include "hal_timer.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"
#include <stdbool.h>


static repeating_timer_t timer;
static hal_timer_cb_t user_cb = 0;

static bool timer_irq(struct repeating_timer *t) {
    if (user_cb) user_cb();
    return true;
}

void hal_timer_init(uint32_t tick_us, hal_timer_cb_t cb) {
    user_cb = cb;
    add_repeating_timer_us(-(int64_t)tick_us, timer_irq, NULL, &timer);
}
