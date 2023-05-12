// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "hardware.h"
#include "configurations.h"

#ifndef ARDUINO_ACCESS_SYSTEM_SIGNALISATION_
#define ARDUINO_ACCESS_SYSTEM_SIGNALISATION_

class Signalisation
{
public:
    Signalisation();
    void positive();
    void positiveSound();
    void removedMember();
    void whitelistFull();
    void endKeying();
    void permDenied();
    void reject();
    void close();
    void resetWhitelist();
    void fullReset();
};

#endif // ARDUINO_ACCESS_SYSTEM_SIGNALISATION_