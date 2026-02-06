#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

/* ticks globales del sistema */
extern volatile uint64_t nk_ticks;

/* API */
void kernel_init(void);
void kernel_launch_apps(void);

#endif
