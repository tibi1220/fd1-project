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

#define A_LEN 6
#define DO_LEN 16
#define MEMORY_SIZE 64
#define MESSAGE_LENGTH 32


void increment_address(unsigned char *p);
void decrement_address(unsigned char *p);
void eeprom_93c46_init();
unsigned int eeprom_93c46_read(
        int int_address,
        unsigned char *ptr
        );
// char eeprom_93c46_read(unsigned char address);