#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

typedef void (*task_fn_t)(void);

/* API */
void scheduler_init(void);
void scheduler_start(void);
void scheduler_tick(void);

void task_create(task_fn_t fn, uint32_t stack_size);
void scheduler_sleep(uint64_t until);

#endif
