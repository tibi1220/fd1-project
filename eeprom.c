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

unsigned int eeprom_93c46_read(
    int int_address, 
    unsigned char *ptr
) {
    unsigned char address[A_LEN];
    unsigned char data[DO_LEN];
    // unsigned int weights[data_length];
    
    for(unsigned char i = 0; i < DO_LEN; i++) {
        data[i] = 0;
        // weights[i] = pow(2, i);
    }
    
    for(unsigned char i = 0; i < A_LEN; i++) {
        address[i] = (int_address >> i) & 0b1;
    }
    
    CLK = 0;
    CS = 1;
    DI = 1;
    unsigned int d = 0;
    __delay_ms(50);
    
    // OPCODE: 1 - 1 - 0
    // ___...CS=1,DI=1...___|‾‾‾‾‾‾‾‾‾‾|_DI=1_|‾‾‾‾‾‾‾‾‾‾|_DI=0_
    CLK = 1;
    
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    
    CLK = 0;
    
    Nop(); Nop(); Nop(); Nop();
    DI = 1; Nop();
    Nop(); Nop(); Nop(); Nop();
    
    CLK = 1;
    
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    
    CLK = 0;
    
    Nop(); Nop(); Nop(); Nop();
    DI = 0; Nop();
    Nop(); Nop(); Nop(); Nop();
    
    // Address
    // |‾‾‾‾‾‾‾‾‾‾|_AD5_|‾‾‾‾‾‾‾‾‾‾|_AD4_|‾‾‾‾‾‾‾‾‾‾|_AD3_|‾‾‾‾‾‾‾‾‾‾|_AD2_|‾‾‾‾‾‾‾‾‾‾|_AD1_|‾‾‾‾‾‾‾‾‾‾|_AD0_
    for(int i = A_LEN - 1; i >= 0; i--) {
        CLK = 1;
        
        Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
        
        CLK = 0;
        
        Nop(); Nop(); Nop();
        DI = address[i]; Nop();
        Nop(); Nop(); Nop();
    }
    
    // Data out
    // |‾‾‾‾‾‾‾‾‾‾|_DOF_|‾‾‾‾‾‾‾‾‾‾|_DOE_|‾‾‾‾‾‾‾‾‾‾|_..._|‾‾‾‾‾‾‾‾‾‾|_DO1_|‾‾‾‾‾‾‾‾‾‾|_DO0_
    for(int i = DO_LEN - 1; i >= 0; i--) {
        CLK = 1;
        
        Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
        
        CLK = 0;
        
        Nop(); Nop(); Nop();
        data[i] = DO; Nop();
        Nop(); Nop(); Nop();
    }
    
    // Deselect chip
    // |‾‾‾‾‾CS=0,DI=0‾‾‾‾‾|__...__
    CLK = 1;
    
    Nop(); Nop(); Nop(); Nop();
    CS = 0; Nop();
    DI = 0; Nop();
    Nop(); Nop(); Nop(); Nop();
    
    CLK = 0;
    
    for(char i = 0; i < DO_LEN; i++) {
        d += data[i] * pow(2, i);
    }
    
    ptr = data;
    return d;
}

