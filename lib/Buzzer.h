// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>

#ifndef ARDUINO_ACCESS_SYSTEM_BUZZER_
#define ARDUINO_ACCESS_SYSTEM_BUZZER_

class Buzzer
{
private:
    uint8_t _pin;

public:
    Buzzer(uint8_t pin);
    void play(uint16_t freq);
    void pause();
};

#endif // ARDUINO_ACCESS_SYSTEM_BUZZER_