#include "nkernel.h"

extern volatile uint64_t nk_ticks;
extern void scheduler_sleep(uint64_t until);

void nk_sleep_ms(uint32_t ms) {
    scheduler_sleep(nk_ticks + ms);
}
