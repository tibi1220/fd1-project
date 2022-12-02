#include "buttons.h"
#include "eeprom.h" 
#include "lcd.h"
#include "led.h"

#ifndef FD1_H
#define FD1_H
#include "fd1.h"
#endif

int main(void) {
    // Main function starts here

    led_init();

    lcd_init();
    lcd_cgram();
    lcd_cls();

    buttons_init();

    eeprom_93c46_init();

    lcd_cls();
    sprintf(lcd, "NA(D1J5ZG) 93c46");
    sprintf(lcd + LCD_WIDTH, "ST(C7XUDE)READER");
    lcd_update();

    __delay_ms(2000);

    void* debugger;
    unsigned char address = 0;
    int button_id = -1;
    unsigned int data = eeprom_93c46_read(address, debugger);
    char c = (data & 0xFF00) >> 8;
    char state = 0;
    char message[MEMORY_SIZE];
    char j = 0;

    lcd_cls();
    sprintf(lcd, "Memcim:0x%02X/0x%02X", address, MEMORY_SIZE);
    sprintf(lcd + LCD_WIDTH, "HEX:0x%02X, CHAR:%c ", c, c);
    lcd_update();

    // Infinite while loop starts here
    while (1) {
        switch (state) {
            case 0:
                button_id = get_pressed_button();
                if (button_id == -1) break;

                debounce_button(button_id);

                if (button_id == 0) {
                    decrement_address(&address);
                } else if (button_id == 1) {
                    increment_address(&address);
                } else if (button_id == 12) {
                    address = 0;
                }else if (button_id == 13) {
                    state = 1;
                    break;
                }

                data = eeprom_93c46_read(address, debugger);
                char c = data >> 8;

                lcd_cls();
                sprintf(lcd, "Memcim:0x%02X/0x%02X", address, MEMORY_SIZE);
                sprintf(lcd + LCD_WIDTH, "HEX:0x%02X, CHAR:%c", c, c);
                lcd_update();

                break;

            case 1:
                lcd_cls();
                sprintf(lcd, "Easter egg:00/%d", MEMORY_SIZE);
                sprintf(lcd + LCD_WIDTH, "Teljes uzi tolt");
                lcd_update();

                j = 0;
                state = 2;

                for (char i = 0; i < MEMORY_SIZE; i++) {
                    message[i] = eeprom_93c46_read(i, debugger) >> 8;
                    lcd_cls();
                    sprintf(lcd, "Easter egg:%02d/%d", i + 1, MEMORY_SIZE);
                    sprintf(lcd + LCD_WIDTH, "Teljes uzi tolt");
                    lcd_update();
                }

            case 2:
                lcd_cls();
                sprintf(lcd, "%s", message + j * LCD_WIDTH * LCD_HEIGHT);
                lcd_update();

                button_id = -1;
                while (button_id == -1) {
                    button_id = get_pressed_button();
                }

                debounce_button(button_id);

                if (button_id == 0) {
                    j ^= 1;
                } else if (button_id == 1) {
                    j ^= 1;
                } else if (button_id == 13) {
                    state = 0;
                    lcd_cls();
                    sprintf(lcd, "Memcim:0x%02X/0x%02X", address, MEMORY_SIZE);
                    sprintf(lcd + LCD_WIDTH, "HEX:0x%02X, CHAR:%c", c, c);
                    lcd_update();
                    break;
                }

                break;
        }

    } // Infinite while loop ends here
    // Main function ends here (unreachable code)
    return 0;
}
