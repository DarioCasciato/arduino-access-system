// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "../lib/Buzzer.h"
#include "../lib/LED.h"
#include "../lib/SK6812.h"
#include "../lib/Keypad.h"
#include <MFRC522.h>
#include "configurations.h"

#ifndef ARDUINO_ACCESS_SYSTEM_HARDWARE_
#define ARDUINO_ACCESS_SYSTEM_HARDWARE_

namespace Hardware
{
    void init();
    // RGB LED
    SK6812 ledSignalization(1);

    // Buzzer
    Buzzer buzzer(SIGNALIZER_BUZZER);

    // RFID Reader
    MFRC522 reader(SS_PIN, RST_PIN);
    MFRC522::StatusCode status;
    MFRC522::MIFARE_Key key;

    // access LED
    LED accessLED(SIGNALIZER_OPENER);

    // Keypad
    //! Keypad keypad();

} // namespace Hardware

#endif // ARDUINO_ACCESS_SYSTEM_HARDWARE_