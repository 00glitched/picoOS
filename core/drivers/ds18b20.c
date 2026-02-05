#include "ds18b20.h"
#include "hal/hal_gpio.h"
#include "hal/hal_timer.h"

#define ONEWIRE_DELAY_US(us) busy_wait_us_32(us)

/* --- 1-Wire low level --- */

static void ow_low(uint8_t pin) {
    hal_gpio_init(pin, HAL_GPIO_OUT);
    hal_gpio_write(pin, 0);
}

static void ow_release(uint8_t pin) {
    hal_gpio_init(pin, HAL_GPIO_IN);
}

static uint8_t ow_read(uint8_t pin) {
    return hal_gpio_read(pin);
}

static int ow_reset(uint8_t pin) {
    ow_low(pin);
    busy_wait_us_32(480);
    ow_release(pin);
    busy_wait_us_32(70);
    int presence = !ow_read(pin);
    busy_wait_us_32(410);
    return presence;
}

static void ow_write_bit(uint8_t pin, uint8_t b) {
    ow_low(pin);
    busy_wait_us_32(b ? 6 : 60);
    ow_release(pin);
    busy_wait_us_32(b ? 64 : 10);
}

static uint8_t ow_read_bit(uint8_t pin) {
    uint8_t r;
    ow_low(pin);
    busy_wait_us_32(6);
    ow_release(pin);
    busy_wait_us_32(9);
    r = ow_read(pin);
    busy_wait_us_32(55);
    return r;
}

static void ow_write_byte(uint8_t pin, uint8_t b) {
    for (int i = 0; i < 8; i++) {
        ow_write_bit(pin, b & 1);
        b >>= 1;
    }
}

static uint8_t ow_read_byte(uint8_t pin) {
    uint8_t r = 0;
    for (int i = 0; i < 8; i++) {
        r >>= 1;
        if (ow_read_bit(pin))
            r |= 0x80;
    }
    return r;
}

/* --- DS18B20 API --- */

int ds18b20_init(ds18b20_t *dev, uint8_t pin) {
    dev->pin = pin;
    return ow_reset(pin);
}

int ds18b20_read_raw(ds18b20_t *dev, int16_t *raw) {
    if (!ow_reset(dev->pin)) return -1;

    ow_write_byte(dev->pin, 0xCC); // skip rom
    ow_write_byte(dev->pin, 0x44); // convert T

    busy_wait_us_32(750000); // wait conversion

    if (!ow_reset(dev->pin)) return -2;

    ow_write_byte(dev->pin, 0xCC);
    ow_write_byte(dev->pin, 0xBE); // read scratchpad

    uint8_t lsb = ow_read_byte(dev->pin);
    uint8_t msb = ow_read_byte(dev->pin);

    *raw = (msb << 8) | lsb;
    return 0;
}

float ds18b20_read_celsius(ds18b20_t *dev) {
    int16_t raw;
    if (ds18b20_read_raw(dev, &raw) != 0) return -1000.0f;
    return raw / 16.0f;
}
