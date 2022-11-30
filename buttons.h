#ifndef FD1_H
#define FD1_H
#include "fd1.h"
#endif

#define MATRIX_COLS 4
#define MATRIX_ROWS 4

// as output (tris = 0)
#define ROW0 LATBbits.LATB0
#define ROW1 LATBbits.LATB1
#define ROW2 LATBbits.LATB2
#define ROW3 LATBbits.LATB3
// as input (tris = 1)
#define COL0 PORTBbits.RB4
#define COL1 PORTBbits.RB5
#define COL2 PORTAbits.RA3
#define COL3 PORTAbits.RA5

void buttons_init();
int get_pressed_button();
void debounce_button(int id);
void run_button_action(int id);