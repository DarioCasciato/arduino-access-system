// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "hardware.h"

void init()
{
    Hardware::reader.PCD_Init();
    Hardware::ledSignalization.set_output(SIGNALIZER_LED);
    Hardware::buzzer.pause();
    Hardware::accessLED.off();
}