// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include "hardware.h"
#include "configurations.h"

#ifndef ARDUINO_ACCESS_SYSTEM_STATE_
#define ARDUINO_ACCESS_SYSTEM_STATE_

namespace State
{
    /// @brief Enumeration of different states
    enum States
    {
        st_noMaster,    ///< No master state
        st_idle,        ///< Idle state
        st_keying       ///< Keying state
    };

    /// @brief State driver function
    void stateDriver();

    /// @brief Handler for the no master state
    void stateNoMaster();

    /// @brief Handler for the idle state
    void stateIdle();

    /// @brief Handler for the keying state
    void stateKeying();
} // namespace State

#endif // ARDUINO_ACCESS_SYSTEM_STATE_