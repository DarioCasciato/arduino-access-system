// =============================================================================
// arduino-access-system | Dario Casciato
// =============================================================================

#include "Arduino.h"
#include "configurations.h"

// Keypad configurations
char keys[KEYPAD_ROW_NUM][KEYPAD_COL_NUM] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'C','0','E'}
};

unsigned char keypad_pin_column[KEYPAD_COL_NUM] = {2, 3, 4};
unsigned char keypad_pin_rows[KEYPAD_ROW_NUM] = {5, 6, 7, 8};
