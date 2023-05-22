// =============================================================================
// arduino-access-system | Dario Casciato
// =============================================================================

#include <Arduino.h>
#include "stdio.h"
#include "whitelist.h"
#include "rfid_utility.h"
#include "signalisation.h"
#include "EdgeDetection.h"

#ifndef ARDUINO_ACCESS_SYSTEM_GENERAL_
#define ARDUINO_ACCESS_SYSTEM_GENERAL_

struct Properties
{
    uint32_t uid;
    bool isMaster;
    bool keyingMasterReset;
    bool startKeying;
};

namespace General
{
    /// @brief Properties struct storing general properties
    extern Properties properties;

    /// @brief Whitelist instance for managing whitelist operations
    extern Whitelist whitelist;

    /// @brief RFID Tag instance for RFID utility operations
    extern Tag rfid;

    /// @brief Signalisation instance for managing signalization
    extern Signalisation signalize;

    /// @brief Value representing tag availability
    extern uint8_t tagAvailableVal;

    /// @brief EdgeDetection instance for tag availability
    extern EdgeDetection tagAvailable;
} // namespace General

#endif // ARDUINO_ACCESS_SYSTEM_GENERAL_