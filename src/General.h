// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "stdio.h"
#include "whitelist.h"
#include "rfid_utility.h"
#include "signalisation.h"
#include "EdgeDetection.h"

#ifndef ARDUINO_ACCESS_SYSTEM_GENERAL_
#define ARDUINO_ACCESS_SYSTEM_GENERAL_

#define LOG_SERIAL(format, ...) Serial.printf(format, ##__VA_ARGS__)

struct badgePresent
{
    uint32_t uid;
    bool isMaster;
};

namespace General
{
    extern badgePresent badge;
    extern Whitelist whitelist;
    extern Tag rfid;
    extern Signalisation signalize;
    extern uint8_t tagAvailableVal;
    extern EdgeDetection tagAvailable;
} // namespace General

#endif // ARDUINO_ACCESS_SYSTEM_GENERAL_