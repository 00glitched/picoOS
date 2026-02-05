#ifndef LED_H
#define LED_H

#include <stdint.h>

void led_init(uint32_t gpio);
void led_on(void);
void led_off(void);
void led_toggle(void);

#endif
