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

    uint16_t _addrWL = 0;
    uint16_t _addrWLCount = 0;
    uint16_t _addrMaster = 0;

    void getWhitelist();
    void getWhitelistCount();
    void getMaster();

public:
    Whitelist(uint16_t addrWL, uint16_t addrWLCount, uint16_t addrMaster);
    void init();
    void remove(uint32_t UID);
    bool add(uint32_t UID);
    void reset();
    bool isMember(uint32_t UID);
    void masterSet(uint32_t UID);
    void masterReset();

    uint32_t getRegisteredMaster() { return registeredMaster; };
};

#endif // ARDUINO_ACCESS_SYSTEM_WHITELIST_