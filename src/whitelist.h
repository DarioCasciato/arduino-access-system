// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "hardware.h"
#include "configurations.h"

#ifndef ARDUINO_ACCESS_SYSTEM_WHITELIST_
#define ARDUINO_ACCESS_SYSTEM_WHITELIST_

class Whitelist
{
private:
    uint8_t whitelistMemberCount = 0;
    uint32_t whitelistMember[WHITELIST_SIZE] = {0};
    uint32_t registeredMaster = 0;

    void getWhitelist();
    void getWhitelistCount();

public:
    void remove(uint32_t UID);
    void add(uint32_t UID);
    void reset();
    bool isMember(uint32_t UID);
    void masterSet(uint32_t UID);
    void masterReset();
};

#endif // ARDUINO_ACCESS_SYSTEM_WHITELIST_