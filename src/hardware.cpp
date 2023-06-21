// =============================================================================
// arduino-access-system | Dario Casciato
// =============================================================================

#include <Arduino.h>
#include <SPI.h>
#include "hardware.h"

namespace Hardware
{
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

    //keypad
    Keypad keypad(
        makeKeymap(keys),
        keypad_pin_rows,
        keypad_pin_column,
        KEYPAD_ROW_NUM,
        KEYPAD_COL_NUM
    );
} // namespace Hardware

void Hardware::init()
{
    SPI.begin();
    Hardware::reader.PCD_Init();
    Hardware::buzzer.pause();
    Hardware::accessLED.off();
    Hardware::ledSignalization.set_output(SIGNALIZER_LED);
    delay(10);
    Hardware::ledSignalization.set_rgbw(0, {0, 0, 0, 0});
    delay(10);
    Hardware::ledSignalization.sync();
}
