#include <stdint.h>
#ifndef SCHEDULER_H
#define SCHEDULER_H

void scheduler_init(void);
void scheduler_start(void);
void scheduler_tick(void);
void scheduler_sleep(uint64_t until);


#endif
