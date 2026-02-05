#include "drivers/led.h"
#include "pico/stdlib.h"

#define LED_PIN 25

void blink_test(void) {
    led_init(LED_PIN);

    while (1) {
        led_toggle();
        sleep_ms(500);
    }
}
