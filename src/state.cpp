// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "state.h"
#include "General.h"

using namespace General;

void accessGranted();


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

    }

    void stateIdle()
    {

    }

    void stateKeying()
    {

    }
} // namespace State



void accessGranted()
{
    Hardware::accessLED.on();
    signalize.positive();
    delay(OPEN_TIME * 1000);

    Hardware::accessLED.off();
}