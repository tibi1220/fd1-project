#include "eeprom.h"

void eeprom_93c46_init() {
    TRISCbits.TRISC3 = 0; // Output
    TRISCbits.TRISC5 = 0; // Output

    TRISAbits.TRISA1 = 0; // Output
    TRISAbits.TRISA2 = 0; // Output

    TRISCbits.TRISC4 = 1; // Input

    // Chip select active
    CS = 0;

    // Digital
    ADCON0 = 0x00;
    ADCON1 = 0x0F;

    CLK = 0;
}

void toggle_clk() {
    CLK ^= 1;
}

void delay_clk_full() {
    __delay_ns(500);
}

void delay_clk_half() {
    __delay_ns(250);
}

void clk_before() {
    CLK ^= 1;
    __delay_ns(500);
    CLK ^= 1;
    __delay_ns(250);
}

void clk_after() {
    __delay_ns(250);
}

void clk_full() {
    CLK ^= 1;
    __delay_ns(500);
    CLK ^= 1;
    __delay_ns(500);
}

unsigned int eeprom_93c46_read(
    unsigned char a5, 
    unsigned char a4, 
    unsigned char a3, 
    unsigned char a2, 
    unsigned char a1, 
    unsigned char a0
) {
    CLK = 0;
    CS = 1;
    __delay_ms(100);

    clk_full();
    clk_full();
    clk_full();

    // OPCODE 1-1-0
    clk_before();
    DI = 1;
    clk_after();

    clk_before();
    DI = 1;
    clk_after();

    clk_before();
    DI = 0;
    clk_after();

    // Address
    clk_before();
    DI = a5;
    clk_after();
    
    clk_before();
    DI = a4;
    clk_after();
    
    clk_before();
    DI = a3;
    clk_after();
    
    clk_before();
    DI = a2;
    clk_after();
    
    clk_before();
    DI = a1;
    clk_after();
    
    clk_before();
    DI = a0;
    clk_after();
    
    unsigned int d = 0;
    
    // Data out
    for(unsigned char i = 15; i >= 0; i++) {
        clk_before();
        d += pow(DO, i);
        clk_after();
    }
    
    DI = 0;
    
    return d;
}