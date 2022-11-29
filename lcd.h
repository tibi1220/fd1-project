#ifndef FD1_H
#define FD1_H
#include "fd1.h"
#endif

#define LCD_WIDTH 16 // LCD is 16 char wide
#define LCD_HEIGHT 2 // LCD is 2 char tall
#define LCD_DATA LATD // LCD data on LATD registers
#define LCD_RS LATEbits.LATE0 // LCD register select
#define LCD_RW LATEbits.LATE1 // LCD read/write
#define LCD_E LATEbits.LATE2 // LCD enable
#define LCD_BF PORTDbits.RD7 // LCD data last register

extern char lcd[LCD_WIDTH*LCD_HEIGHT + 1];

void lcd_init();
void lcd_update();
void lcd_cls();
void lcd_cgram();