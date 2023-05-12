// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include <MFRC522.h>
#include "hardware.h"

#ifndef ARDUINO_ACCESS_SYSTEM_RFID_UTILITY_
#define ARDUINO_ACCESS_SYSTEM_WHITELIST_

class Tag
{
public:
    Tag();
    bool checkMaster();
    bool tagPresent();
    uint32_t getUID();
};

#endif // ARDUINO_ACCESS_SYSTEM_WHITELIST_