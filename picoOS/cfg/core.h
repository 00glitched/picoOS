#ifndef PICO_CORE_H
#define PICO_CORE_H

// hardware
#define CFG_CORE_CORES 2
#define CFG_CORE_FREEFLASH 12
#define CFG_CORE_TICKUS 1000
#define CFG_CORE_MAXTASK 4

void core_init(void);
void core_tick(void);

#endif
