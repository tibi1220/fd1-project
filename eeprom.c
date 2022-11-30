#include "eeprom.h"

enum EEPROM_STATE {
    STANDBY,
    SET_READ,
    SET_ADDRESS,
    READ,
    FINISHED
};

enum EEPROM_STATE state = STANDBY;
int h = 0;
unsigned int d = 0;
int a[6] = {0, 0, 0, 0, 0, 0};

void __attribute__((__interrupt__, __auto_psv__))
_T1Interrupt(void) {
    PIR1bits.TMR1IF = 0;

    if (state == STANDBY) return;
    CLK ^= 1;

    if (CLK == 0) {
        switch (state) {
                // DI 1 - 1 - 0
            case SET_READ:
                switch (h) {
                    case 0:
                        DI = 1;
                        h++;
                        break;
                    case 1:
                        DI = 1;
                        h++;
                        break;
                    case 2:
                        DI = 0;
                        h = 0;
                        d = 0;
                        state = SET_ADDRESS;
                        break;
                }
                break;

                // Wait 6 cycles
            case SET_ADDRESS:
                DI = a[h];
                if (++h == 5) {
                    h = 16;
                    state = READ;
                }
                break;

                // Get 16 data bits
            case READ:
                d += pow(DO, h--);
                if (h == 0) {
                    state = FINISHED;
                }
                break;

            case FINISHED:
                DI = 0;
                break;

            default:
                break;
        }
    }
}

void eeprom_93c46_init() {
    TRISCbits.TRISC3 = 0; // Output
    TRISCbits.TRISC5 = 0; // Output

    TRISAbits.TRISA1 = 0; // Output
    TRISAbits.TRISA2 = 0; // Output

    TRISCbits.TRISC4 = 1; // Input

    // Chip select active
    CS = 1;

}

unsigned int eeprom_93c46_read(unsigned char address) {
    // a = {0, 0, 0, 0, 0, 0}; //address;

    state = SET_READ;
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    IPR1bits.TMR1IP = 1;

    while (state != FINISHED) Nop();

    state = STANDBY;

    PIE1bits.TMR1IE = 0;

    return d;
}