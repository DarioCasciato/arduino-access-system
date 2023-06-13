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

namespace EventsPinEntry
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

namespace EventsKeypadConfig
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
        st_pinEntry,    ///< Pin Entry state
        st_keying,      ///< Keying state
        st_keypadConfig ///< Keypad Configuration state
    };

    /// @brief  @brief initializes state variable
    void onStart();

    /// @brief State driver function
    void stateDriver();

    /// @brief Handler for the no master state
    void stateNoMaster();

    /// @brief Handler for the idle state
    void stateIdle();

    /// @brief Handler for the pin entry state
    void statePinEntry();

    /// @brief Handler for the keying state
    void stateKeying();

    /// @brief Handler for the keypad configuration state
    void stateKeypadConfig();

    /// @brief Function to handle events based on the state
    ///
    /// @param state The EdgeEvents struct containing event functions
    void eventCaller(EdgeEvents state);
} // namespace State


#endif // ARDUINO_ACCESS_SYSTEM_STATE_