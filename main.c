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

    int a = DO;
    
    lcd_cls();
    sprintf(lcd, "Hello World!%d", a);
    lcd_update();

    // __delay_ms(2000);

    unsigned int data[MEMORY_SIZE];
    // unsigned char bits[64][16];
    // unsigned char* (ptr[64]);
    void* ptr;
    char c = 0;
    
    for (char i = 0 + c; i < 8 + c; i++) {
        lcd_cls();
        sprintf(lcd, "Hello World! %d ", i);
        lcd_update();
        data[i] = eeprom_93c46_read(i, ptr);
    }

    lcd_cls();
    for (char i = 0; i < 8; i++) {
        sprintf(lcd + 4 * i, "%02X", data[i + c]);
    }
    lcd_update();


    // Infinite while loop starts here
    while (1) {
        Nop();
    } // Infinite while loop ends here
    // Main function ends here (unreachable code)
    return 0;
}
