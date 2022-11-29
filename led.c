#include "led.h"

void led_init() {
    // Use PORTD as output
    TRISD = 0x00;
    // Turn off all LED
    D1 = 0;
    D2 = 0;
    D3 = 0;
    D4 = 0;
    D5 = 0;
    D6 = 0;
    D7 = 0;
    D8 = 0;
}