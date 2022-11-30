#ifndef FD1_H
#define FD1_H
#include "fd1.h"
#endif

// IC3 -- 93C46
#define CS PORTAbits.RA2
#define CLK PORTCbits.RC3
#define DI PORTCbits.RC5
#define DO PORTCbits.RC4

// READ OPCODE
#define OPCODE 0b10

void eeprom_93c46_init();
unsigned int eeprom_93c46_read(
    unsigned char a5, 
    unsigned char a4, 
    unsigned char a3, 
    unsigned char a2, 
    unsigned char a1, 
    unsigned char a0
);
// char eeprom_93c46_read(unsigned char address);