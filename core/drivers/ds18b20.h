#pragma once
#include <stdint.h>

typedef struct {
    uint8_t pin;
} ds18b20_t;

int  ds18b20_init(ds18b20_t *dev, uint8_t pin);
int  ds18b20_read_raw(ds18b20_t *dev, int16_t *raw);
float ds18b20_read_celsius(ds18b20_t *dev);
