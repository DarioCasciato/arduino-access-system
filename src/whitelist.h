// =============================================================================
// arduino-access-system | Dario Casciato
// =============================================================================

#include <Arduino.h>
#include "hardware.h"
#include "configurations.h"

#ifndef ARDUINO_ACCESS_SYSTEM_WHITELIST_
#define ARDUINO_ACCESS_SYSTEM_WHITELIST_


/// @brief Writes registered pin to EEPROM
/// @param addrOffset Address of pin in EEPROM
/// @param strToWrite Pin to save
void writePinToEEPROM(int addrOffset, const String &strToWrite);

/// @brief Reads pin from EEPROM
/// @param addrOffset Address of pin
/// @return pin from EEPROM
String readPinFromEEPROM(int addrOffset);


class Whitelist
{
private:
    uint8_t whitelistMemberCount = 0;
    uint32_t whitelistMember[WHITELIST_SIZE] = {0};
    uint32_t registeredMaster = 0;
    String registeredPin;
    bool pinIsRegistered = false;

    uint16_t _addrWL = 0;
    uint16_t _addrWLCount = 0;
    uint16_t _addrMaster = 0;
    uint16_t _addrPin = 0;

    /// @brief Get the whitelist from EEPROM
    void getWhitelist();

    /// @brief Get the whitelist count from EEPROM
    void getWhitelistCount();

    /// @brief Get the registered master value from EEPROM
    void getMaster();

    /// @brief get the registered pin from EEPROM
    void getPin();

public:
    /// @brief Whitelist constructor
    ///
    /// @param addrWL The EEPROM address of the whitelist
    /// @param addrWLCount The EEPROM address of the whitelist count
    /// @param addrMaster The EEPROM address of the registered master value
    Whitelist(uint16_t addrWL, uint16_t addrWLCount, uint16_t addrMaster, uint16_t addrPin);

    /// @brief Remove a UID from the whitelist
    ///
    /// @param UID The UID to be removed
    void remove(uint32_t UID);

    /// @brief Add a UID to the whitelist
    ///
    /// @param UID The UID to be added
    /// @return True if the UID was added successfully, false if the whitelist is full
    bool add(uint32_t UID);

    /// @brief Reset the whitelist
    void reset();

    /// @brief Check if a UID is a member of the whitelist
    ///
    /// @param UID The UID to be checked
    /// @return True if the UID is a member of the whitelist, false otherwise
    bool isMember(uint32_t UID);

    /// @brief Set the registered master UID
    ///
    /// @param UID The UID to be set as the registered master
    void masterSet(uint32_t UID);

    /// @brief Reset the registered master UID
    void masterReset();

    /// @brief  Sets the new keypad pin
    /// @param newPin New Pin that is being registered
    void pinSet(String newPin);

    /// @brief Resets registered pin
    void pinReset();

    /// @brief checks if pin corresponds with registered pin
    /// @param checkPin pin that is passed to check
    /// @return 1 if corresponds to registered pin
    bool pinCheck(String checkPin);

    /// @brief Get the registered master UID
    ///
    /// @return The registered master UID
    uint32_t getRegisteredMaster() { return registeredMaster; };

    /// @brief Get the registered master UID
    ///
    /// @return The registered master UID
    uint16_t getWhitelistMemberCount() { return whitelistMemberCount; };

    /// @brief checks if a pin is registered
    /// @return 1 if a pin is registered
    bool isPinRegistered() { return pinIsRegistered; };

    /// @brief Initialize the whitelist
    void init();
};

#endif // ARDUINO_ACCESS_SYSTEM_WHITELIST_