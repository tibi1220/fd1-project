#include "lcd.h"

char lcd[LCD_WIDTH*LCD_HEIGHT + 1];

void lcd_data(unsigned char b, unsigned char rs) {
    unsigned char bf;

    // Save TRISD state
    unsigned char trisd_backup = TRISD;

    // Set registers
    LCD_RS = rs;
    LCD_DATA = b;

    // Wait
    Nop();
    Nop();
    Nop();

    // Enable
    LCD_E = 1;

    // Wait
    Nop();
    Nop();
    Nop();

    // Disable
    LCD_E = 0;

    // Wait
    Nop();
    Nop();
    Nop();

    // Set registers
    LCD_DATA = 0x00;
    TRISD = 0xFF;
    LCD_RW = 1;
    LCD_RS = 0;

    // Wait
    Nop();
    Nop();
    Nop();

    do {
        LCD_E = 1;

        Nop();
        Nop();
        Nop();

        bf = LCD_BF;
        LCD_E = 0;

        Nop();
        Nop();
        Nop();
    } while (bf);

    TRISD = trisd_backup;
    LCD_RW = 0;
}

void lcd_init() {
    TRISD = 0x00; // LCD DATA as output
    TRISEbits.TRISE0 = 0; // LCD RS as output
    TRISEbits.TRISE1 = 0; // LCD RW as output
    TRISEbits.TRISE2 = 0; // LCD E as output

    // Wait for init
    LCD_RW = 0;
    __delay_ms(50);

    lcd_data(0x38, 0); // a row display, 5x8 char size
    lcd_data(0x0E, 0); // display on, cursor on, blink off
    lcd_data(0x01, 0); // clear display
    lcd_data(0x02, 0); // go home
    lcd_data(0x06, 0); // entry mode set
    lcd_cls();
}

void lcd_cls() {
    memset(lcd, ' ', LCD_WIDTH * LCD_HEIGHT);
}

void lcd_update() {
    // Upper row
    lcd_data(0x80, 0);
    for (int i = 0; i < LCD_WIDTH; i++) lcd_data(lcd[i], 1);
    // Lower row
    lcd_data(0xc0, 0);
    for (int i = 0; i < LCD_WIDTH; i++) lcd_data(lcd[i + LCD_WIDTH], 1);
}

void lcd_cgram() {
    lcd_data(0x40, 0); // set cgram, define char 0
    lcd_data(0x00, 1); // 0
    lcd_data(0x0a, 1); // 1
    lcd_data(0x15, 1); // 2
    lcd_data(0x11, 1); // 3
    lcd_data(0x0a, 1); // 4
    lcd_data(0x04, 1); // 5
    lcd_data(0x00, 1); // 6
    lcd_data(0x00, 1); // 7
}