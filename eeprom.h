#ifndef FD1_H
#define FD1_H
#include "fd1.h"
#endif

// IC3 -- 93C46
#define CS PORTAbits.RA2
#define CLK PORTCbits.SCK
#define DI PORTCbits.SDI
#define DO PORTCbits.SDO

// READ OPCODE
#define OPCODE 0b10

void eeprom_93c46_init();
char eeprom_93c46_read(unsigned char address);