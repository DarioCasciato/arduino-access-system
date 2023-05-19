// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "state.h"
#include "General.h"


namespace State
{
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
        if(General::tagAvailable.getEdgePos())
        {
            if(General::badge.isMaster)
                Hardware::accessLED.on();
            else
                Hardware::accessLED.off();
        }

        Serial.println(General::tagAvailable.getActState());
    }

    void stateIdle()
    {

    }

    void stateKeying()
    {

    }
} // namespace State


