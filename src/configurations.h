// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#ifndef ARDUINO_ACCESS_SYSTEM_CONFIGURATIONS_
#define ARDUINO_ACCESS_SYSTEM_CONFIGURATIONS_

// Pin definitions
#define RST_PIN 9
#define SS_PIN 10

#define SIGNALIZER_BUZZER 14
#define SIGNALIZER_LED 15
#define SIGNALIZER_OPENER 17

// How long the Lock should be open after authentication in seconds
#define OPEN_TIME 3

// Define size of Whitelist (depends on RAM size of Controller)
#define WHITELIST_SIZE 100

// Adresses of Whitelist Values in EEPROM
#define ADDRESS_WHITELIST 0x020
#define ADDRESS_WHITELISTCOUNT 0x005
#define ADDRESS_MASTER 0x010

#endif // ARDUINO_ACCESS_SYSTEM_CONFIGURATIONS_