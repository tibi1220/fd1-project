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

void clk_before() {
    CLK = 1;
    Nop(); Nop(); Nop(); 
}

void clk_after() {
    Nop(); Nop(); Nop();
    CLK = 0;
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
}

void clk_full() {
    CLK = 1;
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    CLK = 0;
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
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
    unsigned int d = 0;
    __delay_ms(50);

    // 3 full clock
    // ___...___|‾‾‾‾‾‾‾‾|________|‾‾‾‾‾‾‾‾|________|‾‾‾‾‾‾‾‾|________
    clk_full();
    clk_full();
    clk_full();

    // Write OP-code
    // |‾‾‾‾‾DI=1‾‾‾‾‾|____|‾‾‾‾‾DI=1‾‾‾‾‾|____|‾‾‾‾‾DI=0‾‾‾‾‾|____
    clk_before();
    DI = 1; Nop(); Nop(); Nop();
    clk_after();

    clk_before();
    DI = 1; Nop(); Nop(); Nop();
    clk_after();

    clk_before();
    DI = 0; Nop(); Nop(); Nop();
    clk_after();

    // Address
    // |‾‾ad5‾‾|____|‾‾ad4‾‾|____|‾‾ad3‾‾|____|‾‾ad2‾‾|____|‾‾ad1‾‾|____|‾‾ad0‾‾|____
    clk_before();
    DI = a5; Nop(); Nop(); Nop();
    clk_after();
    
    clk_before();
    DI = a4; Nop(); Nop(); Nop();
    clk_after();
    
    clk_before();
    DI = a3; Nop(); Nop(); Nop();
    clk_after();
    
    clk_before();
    DI = a2; Nop(); Nop(); Nop();
    clk_after();
    
    clk_before();
    DI = a1; Nop(); Nop(); Nop();
    clk_after();
    
    clk_before();
    DI = a0; Nop(); Nop(); Nop();
    clk_after();
    
    clk_full();
    
    // Data out
    // |‾‾DOF‾‾|____|‾‾DOE‾‾|____|‾‾...‾‾|____|‾‾DO1‾‾|____|‾‾DO0‾‾|____
    for(int i = 15; i >= 0; i--) {
        CLK = 1;
        Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
        CLK = 0;
        Nop(); Nop(); Nop();
        d += DO * pow(2, i);
        Nop(); Nop(); Nop();
    }
    
    // Deselect chip
    // |‾‾‾‾‾CS=0, DI=0‾‾‾‾‾|____...___
    clk_before();
    CS = 0; Nop();
    DI = 0; Nop();
    clk_after();
    
    return d;
}