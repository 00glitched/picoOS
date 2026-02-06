#include <stdint.h>
#include "led.h"
#include "core/hal/hal_gpio.h"

static uint32_t led_gpio;

void led_init(uint32_t gpio) {
    led_gpio = gpio;
    hal_gpio_init(led_gpio, 1);
}

void led_on(void) {
    hal_gpio_write(led_gpio, 1);
}

void led_off(void) {
    hal_gpio_write(led_gpio, 0);
}

void led_toggle(void) {
    hal_gpio_toggle(led_gpio);
}
