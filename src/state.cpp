// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "state.h"

namespace General
{
    badgePresent badge = {0};
    Whitelist whitelist(ADDRESS_WHITELIST, ADDRESS_WHITELISTCOUNT, ADDRESS_MASTER);
    Tag rfid;
    Signalisation signalize;

    uint8_t tagAvailableVal;
    EdgeDetection tagAvailable(&tagAvailableVal);
} // namespace General


namespace State
{
    using namespace General;

    States state = States::st_noMaster;
    void stateDriver()
    {
        switch (State::state)
        {
        case States::st_noMaster: State::stateNoMaster(); break;
        case States::st_idle: State::stateIdle(); break;
        case States::st_keying: State::stateKeying(); break;

        default:
            break;
        }
    }


    void stateNoMaster()
    {
        if(tagAvailable.getEdgePos())
        {
            if(badge.isMaster)
                Hardware::accessLED.on();
            else
                Hardware::accessLED.off();
        }
    }

    void stateIdle()
    {

    }

    void stateKeying()
    {

    }
} // namespace State


