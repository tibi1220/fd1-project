#ifndef FD1_H
#define FD1_H
#include "fd1.h"
#endif

#include "buttons.h"
#include "eeprom.h" 
#include "lcd.h"
#include "led.h"

int main(void) {
    // Main function starts here

    led_init();

    buttons_init();

    lcd_init();
    lcd_cgram();
    lcd_cls();

    eeprom_93c46_init();

    int i = 0;
    int id = -1;
    int state = 0;
    unsigned int d;

    lcd_cls();
    sprintf(lcd, "Hello World!%d", i);
    lcd_update();

    // Infinite while loop starts here
    while (1) {
        switch (state) {
            case 0:
                id = get_pressed_button();
                if (id == -1) continue;

                debounce_button(id);
                i += id;

                if (id == 15) {
                    state = 1;
                    break;
                }

                lcd_cls();
                sprintf(lcd, "Hello World!%d", i);
                lcd_update();

                break;

            case 1:
                d = eeprom_93c46_read(0);

                lcd_cls();
                sprintf(lcd, "%d", d);
                sprintf(lcd + LCD_WIDTH, "0x%X", d);
                lcd_update();

                __delay_ms(5000);

                state = 2;

                break;

            case 2:
                break;
        }

    } // Infinite while loop ends here

    // Main function ends here (unreachable code)
    return 0;
}
