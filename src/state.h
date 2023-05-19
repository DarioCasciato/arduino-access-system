// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include "hardware.h"
#include "configurations.h"

#ifndef ARDUINO_ACCESS_SYSTEM_STATE_
#define ARDUINO_ACCESS_SYSTEM_STATE_

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