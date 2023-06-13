// =============================================================================
// arduino-access-system | Dario Casciato
// =============================================================================

#ifndef ARDUINO_ACCESS_SYSTEM_CONFIGURATIONS_
#define ARDUINO_ACCESS_SYSTEM_CONFIGURATIONS_

// Pin definitions
#define RST_PIN                 9       ///< Reset pin number
#define SS_PIN                  10      ///< Slave Select pin number

#define SIGNALIZER_BUZZER       14      ///< Buzzer pin number for the signalizer
#define SIGNALIZER_LED          15      ///< LED pin number for the signalizer
#define SIGNALIZER_OPENER       17      ///< Opener pin number for the signalizer

#define KEYPAD_ROW_NUM          4
#define KEYPAD_COL_NUM          3

// How long the Lock should be open after authentication in seconds
#define OPEN_TIME               3       ///< Open time duration in seconds

#define TIME_TIMEOUT            10      ///< Timeout time in keying state

// Define size of Whitelist (depends on RAM size of Controller)
#define WHITELIST_SIZE          100     ///< Size of the whitelist

// Addresses of Values in EEPROM
#define ADDRESS_WHITELIST       0x0F0   ///< Address of the whitelist in EEPROM
#define ADDRESS_WHITELISTCOUNT  0x000   ///< Address of the whitelist count value in EEPROM
#define ADDRESS_MASTER          0x006   ///< Address of the master value in EEPROM
#define ADDRESS_KEYPAD_PIN      0x010   ///< Address of registered Keypad Pin


// Keypad
extern char keys[KEYPAD_ROW_NUM][KEYPAD_COL_NUM];
extern unsigned char keypad_pin_column[KEYPAD_COL_NUM];
extern unsigned char keypad_pin_rows[KEYPAD_ROW_NUM];

#endif // ARDUINO_ACCESS_SYSTEM_CONFIGURATIONS_