#include "eeprom.h"

void eeprom_93c46_init() {
    TRISCbits.TRISC3 = 0; // Output
    TRISCbits.TRISC5 = 0; // Output

    TRISAbits.TRISA1 = 0; // Output
    TRISAbits.TRISA2 = 0; // Output

    TRISCbits.TRISC4 = 1; // Input

    // Chip select active
    CS = 1;

    // Sampling mode
    SSPCON1bits.CKP = 0;
    SSPSTATbits.CKE = 0;
    SSPSTATbits.SMP = 0;

    // Interrupt
    IPR1bits.SSPIP = 1;
    PIE1bits.SSPIE = 1;
    PIR1bits.SSPIF = 0;

    // Digital
    ADCON0 = 0x00;
    ADCON1 = 0x0F;
    
    // Enable SSP
    SSPCON1bits.SSPEN = 1;
}

char eeprom_93c46_read(unsigned char address) {
    // Enable SSP
    // SSPCON1bits.SSPEN = 1;
    
    SSPBUF=0xff;		    /* Copy flush byte in SSBUF */
    while(!PIR1bits.SSPIF);	/* Wait for complete 1 byte transmission */
    PIR1bits.SSPIF=0;
    return SSPBUF;		    /* Return received byte */   
    
    // Disable SSP
    // SSPCON1bits.SSPEN = 0;
}