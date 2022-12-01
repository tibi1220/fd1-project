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

    eeprom_93c46_init();

    int id = -1;
    int state = 0;
    unsigned char aa6, aa5, aa4, aa3, aa2, aa1, aa0;

    lcd_cls();
    sprintf(lcd, "Hello World!%d", id);
    lcd_update();

    __delay_ms(2000);

    unsigned char c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;

    unsigned int temp;

    temp = eeprom_93c46_read(0, 0, 0, 0, 0, 0);
    c0 = temp & 0x00FF;
    c1 = temp >> 8;
    
    lcd_cls();
    sprintf(lcd, "%d", temp);
    lcd_update();
    __delay_ms(5000);
    
    temp = eeprom_93c46_read(0, 0, 0, 0, 0, 1);
    c2 = temp & 0x00FF;
    c3 = temp >> 8;
    
    lcd_cls();
    sprintf(lcd, "%d", temp);
    lcd_update();
    __delay_ms(5000);
    
    temp = eeprom_93c46_read(0, 0, 0, 0, 1, 0);
    c4 = temp & 0x00FF;
    c5 = temp >> 8;
    
    lcd_cls();
    sprintf(lcd, "%d", temp);
    lcd_update();
    __delay_ms(5000);
    
    temp = eeprom_93c46_read(0, 0, 0, 0, 1, 1);
    c6 = temp & 0x00FF;
    c7 = temp >> 8;
    
    lcd_cls();
    sprintf(lcd, "%d", temp);
    lcd_update();
    __delay_ms(5000);
    
    temp = eeprom_93c46_read(0, 0, 0, 1, 0, 0);
    c8 = temp & 0x00FF;
    c9 = temp >> 8;
    
    lcd_cls();
    sprintf(lcd, "%d", temp);
    lcd_update();
    __delay_ms(5000);
    

    lcd_cls();
    sprintf(lcd, "%c%c%c%c%c%c%c%c%c%c", c0, c1, c2, c3, c4, c5 , c6, c7, c8, c9);
    sprintf(lcd + LCD_WIDTH, "%x %x %x %x %x %x", c0, c1, c2, c3, c4, c5);
    lcd_update();

    // Infinite while loop starts here
    while (1) {

        Nop();

        /*
        switch (state) {
            case 0:
                id = get_pressed_button();
                if (id == -1) continue;

                debounce_button(id);

                lcd_cls();
                sprintf(lcd, "Hello World!%d", id);
                lcd_update();
                
                __delay_ms(5000);
                state++;
                
                break;
                
            case 1:
                lcd_cls();
                sprintf(lcd, "%d cim olvasasa:", id);
                lcd_update();
                
                aa0 = (id & 0b0000001) >> 0;
                aa1 = (id & 0b0000010) >> 1;
                aa2 = (id & 0b0000100) >> 0;
                aa3 = (id & 0b0001000) >> 1;
                aa4 = (id & 0b0010000) >> 0;
                aa5 = (id & 0b0100000) >> 1;
                aa5 = (id & 0b1000000) >> 1;
                
                long int data = eeprom_93c46_read(aa6, aa5, aa4, aa3, aa2, aa1, aa0);
                
                char c1 = data & 0x00FF;
                
                lcd_cls();
                sprintf(lcd, "HEX: 0x%X", data);
                sprintf(lcd + LCD_WIDTH,  "CHAR: %c", c1);
                lcd_update();
                        
                state--;
                
                break;
        }
         
         */




    } // Infinite while loop ends here

    // Main function ends here (unreachable code)
    return 0;
}
