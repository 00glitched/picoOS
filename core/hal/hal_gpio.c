#include "hal_gpio.h"
#include "hardware/gpio.h"

void hal_gpio_init(uint32_t gpio, int output) {
    gpio_init(gpio);
    gpio_set_dir(gpio, output ? GPIO_OUT : GPIO_IN);
}

void hal_gpio_write(uint32_t gpio, int value) {
    gpio_put(gpio, value);
}

int hal_gpio_read(uint32_t gpio) {
    return gpio_get(gpio);
}

void hal_gpio_toggle(uint32_t gpio) {
    gpio_xor_mask(1u << gpio);
}
