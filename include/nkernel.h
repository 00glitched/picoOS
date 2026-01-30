#ifndef NKERNEL_H
#define NKERNEL_H

#include <stdint.h>

typedef void (*task_fn_t)(void);

void task_create(task_fn_t fn, uint32_t stack_size);
void nk_sleep_ms(uint32_t ms);

#endif
