// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include "hardware.h"
#include "configurations.h"
#include "whitelist.h"
#include "rfid_utility.h"
#include "signalisation.h"
#include "EdgeDetection.h"

#ifndef ARDUINO_ACCESS_SYSTEM_STATE_
#define ARDUINO_ACCESS_SYSTEM_STATE_

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

namespace State
{
    enum States
    {
        st_noMaster,
        st_idle,
        st_keying
    };

    void stateDriver();

    void stateNoMaster();
    void stateIdle();
    void stateKeying();
} // namespace State

#endif // ARDUINO_ACCESS_SYSTEM_STATE_