#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>

void hal_gpio_init(uint32_t gpio, int output);
void hal_gpio_write(uint32_t gpio, int value);
int  hal_gpio_read(uint32_t gpio);
void hal_gpio_toggle(uint32_t gpio);

#endif
