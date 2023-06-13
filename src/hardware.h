// =============================================================================
// arduino-access-system | Dario Casciato
// =============================================================================

#include <Arduino.h>
#include "Buzzer.h"
#include "LED.h"
#include "SK6812.h"
#include "Keypad.h"
#include <MFRC522.h>
#include "configurations.h"

#ifndef ARDUINO_ACCESS_SYSTEM_HARDWARE_
#define ARDUINO_ACCESS_SYSTEM_HARDWARE_


namespace Hardware
{
    /// @brief Initialize the hardware components
    void init();

    // RGB LED
    extern SK6812 ledSignalization;

    // Buzzer
    extern Buzzer buzzer;

    // RFID Reader
    extern MFRC522 reader;
    extern MFRC522::StatusCode status;
    extern MFRC522::MIFARE_Key key;

    // access LED
    extern LED accessLED;

    // Keypad
    extern Keypad keypad;
    extern char keypad_key_buff;
    extern char keypad_key;

} // namespace Hardware

#endif // ARDUINO_ACCESS_SYSTEM_HARDWARE_
