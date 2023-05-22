// =============================================================================
// arduino-access-system | Dario Casciato
// =============================================================================

#include "hardware.h"
#include "configurations.h"

#ifndef ARDUINO_ACCESS_SYSTEM_STATE_
#define ARDUINO_ACCESS_SYSTEM_STATE_

// Forward declaration of EdgeEvents struct
struct EdgeEvents;

// Forward declarations for event namespaces
namespace EventsNoMaster
{
    void edgePos();
    void present();
    void edgeNeg();
}

namespace EventsIdle
{
    void edgePos();
    void present();
    void edgeNeg();
}

namespace EventsKeying
{
    void edgePos();
    void present();
    void edgeNeg();
}


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

    /// @brief Function to handle events based on the state
    ///
    /// @param state The EdgeEvents struct containing event functions
    void eventCaller(EdgeEvents state);
} // namespace State


#endif // ARDUINO_ACCESS_SYSTEM_STATE_