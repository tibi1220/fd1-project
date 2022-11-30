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

    // led_init();

    lcd_init();
    lcd_cgram();
    lcd_cls();
    
    buttons_init();

    // eeprom_93c46_init();

    int i = 0;
    int id = -1;

    lcd_cls();
    sprintf(lcd, "Hello World!%d", i);
    lcd_update();

    // Infinite while loop starts here
    while (1) {
        id = get_pressed_button();
        // if(id == -1) continue;
        
        // debounce_button(id);
        
        i += id;

        lcd_cls();
        sprintf(lcd, "Hello World!%d", id);
        lcd_update();
        
        // __delay_ms(1000);
    } // Infinite while loop ends here

    // Main function ends here (unreachable code)
    return 0;
}
