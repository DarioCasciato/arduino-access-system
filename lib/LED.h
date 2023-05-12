// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>

#ifndef ARDUINO_ACCESS_SYSTEM_LED_
#define ARDUINO_ACCESS_SYSTEM_LED_

enum activeLevel
{
    LOW_ACTIVE,
    HIGH_ACTIVE
};
enum level
{
    OFF,
    ON
};

class LED
{
private:
    uint8_t _pin;
    activeLevel _activeLevel;

public:
    LED(uint8_t pin, activeLevel ActiveLevel = HIGH_ACTIVE);
    void set(level setLevel);
    bool get();
    void toggle();
    void on();
    void off();
};

#endif // ARDUINO_ACCESS_SYSTEM_LED_