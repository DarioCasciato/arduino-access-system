// =============================================================================
// arduino-access-system | Dario Casciato
// =============================================================================

#include <Arduino.h>
#include "hardware.h"
#include "configurations.h"

#ifndef ARDUINO_ACCESS_SYSTEM_SIGNALISATION_
#define ARDUINO_ACCESS_SYSTEM_SIGNALISATION_

class Signalisation
{
public:
    /// @brief Signalisation constructor
    Signalisation();

    /// @brief Perform positive signalization
    void positive();

    /// @brief Perform positive sound signalization
    void positiveSound();

    /// @brief Perform signalization for removed member
    void removedMember();

    /// @brief Perform signalization when the whitelist is full
    void whitelistFull();

    /// @brief Perform end keying signalization
    void endKeying();

    /// @brief Perform permission denied signalization
    void permDenied();

    /// @brief Perform reject signalization
    void reject();

    /// @brief Perform close signalization
    void close();

    /// @brief Reset the whitelist signalization
    void resetWhitelist();

    /// @brief Perform full reset signalization
    void fullReset();

    /// @brief Perform green signalization
    void green();

    /// @brief Fatal Exception occurred
    void exception();
};

#endif // ARDUINO_ACCESS_SYSTEM_SIGNALISATION_