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

#define A_LEN 7
#define DO_LEN 8
#define MEMORY_SIZE 128

void eeprom_93c46_init();
unsigned int eeprom_93c46_read(
        int int_address,
        unsigned char *ptr
        );
// char eeprom_93c46_read(unsigned char address);