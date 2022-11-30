#include "buttons.h"

void buttons_init() {
    // Horizontal as output (B0...3)
    TRISB &= 0b11110000; // Turn off last 4 bits
    // Vertical as input (B4, B5, A3, A5)
    TRISB |= 0b00110000; // Turn on bit 4 and bit 5
    TRISA |= 0b00101000; // Turn on bit 3 and bit 5

    // Use pull ups for RB4 and RB5
    // Enable pull ups
    INTCON2bits.RBPU = 0;

    // Set all rows to 1 (inactive)
    ROW0 = 1;
    ROW1 = 1;
    ROW2 = 1;
    ROW3 = 1;
}

int get_pressed_button_col() {
    if (!COL0) return 0;
    if (!COL1) return 1;
    if (!COL2) return 2;
    if (!COL3) return 3;

    return -1;
}

int get_pressed_button() {
    int col = -1;

    // Check row 0
    ROW0 = 0;
    col = get_pressed_button_col();
    if (col != -1) {
        return col + 0 * MATRIX_COLS;
    }

    // Check row 1
    ROW0 = 1;
    ROW1 = 0;
    col = get_pressed_button_col();
    if (col != -1) {
        return col + 1 * MATRIX_COLS;
    }

    // Check row 2
    ROW1 = 1;
    ROW2 = 0;
    col = get_pressed_button_col();
    if (col != -1) {
        return col + 2 * MATRIX_COLS;
    }

    // Check row 3
    ROW2 = 1;
    ROW3 = 0;
    col = get_pressed_button_col();
    if (col != -1) {
        return col + 3 * MATRIX_COLS;
    }

    // Set row3 to inactive state
    ROW3 = 1;
    return -1;
}

void debounce_col_0() { while(!COL0) Nop(); }
void debounce_col_1() { while(!COL1) Nop(); }
void debounce_col_2() { while(!COL2) Nop(); }
void debounce_col_3() { while(!COL3) Nop(); }

void (*debouncers[])(void) = {
  &debounce_col_0,
  &debounce_col_1,
  &debounce_col_2,
  &debounce_col_3
};

void debounce_button(int id) {
    const int col = id % MATRIX_COLS;
    
    __delay_ms(10);
    (*debouncers[col])();
    __delay_ms(10);
    
    // Set rows to inactive state
    ROW0 = 1;
    ROW1 = 1;
    ROW2 = 1;
    ROW3 = 1;
}

void run_button_action(int id) {
    return;
}