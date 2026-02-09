#ifndef NKERNEL_H
#define NKERNEL_H

#include <stdint.h>
#include "core/kernel/scheduler.h"
#include "core/kernel/kernel.h"


static inline uint64_t nk_now(void) {
    return nk_ticks;
}

static inline void nk_sleep_ms(uint32_t ms) {
    scheduler_sleep(nk_ticks + ms);
}

#endif
