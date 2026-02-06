#include <stdint.h>
#include "scheduler.h"

#define MAX_TASKS 8

typedef struct {
    task_fn_t entry;
    uint32_t  stack_size;
    uint64_t  wake_tick;
    int       sleeping;
} nk_task_t;

static nk_task_t tasks[MAX_TASKS];
static int task_count = 0;
static nk_task_t *current = 0;

extern volatile uint64_t nk_ticks;

void task_create(task_fn_t fn, uint32_t stack_size) {
    if (task_count >= MAX_TASKS) return;

    tasks[task_count].entry = fn;
    tasks[task_count].stack_size = stack_size;
    tasks[task_count].sleeping = 0;
    tasks[task_count].wake_tick = 0;

    task_count++;
}

void scheduler_init(void) {
    task_count = 0;
    current = 0;
}

void scheduler_tick(void) {
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].sleeping && nk_ticks >= tasks[i].wake_tick) {
            tasks[i].sleeping = 0;
        }
    }
}

void scheduler_start(void) {
    while (1) {
        for (int i = 0; i < task_count; i++) {
            if (tasks[i].sleeping) continue;
            current = &tasks[i];
            current->entry();
        }
    }
}

void scheduler_sleep(uint64_t until) {
    if (!current) return;
    current->wake_tick = until;
    current->sleeping = 1;
}
