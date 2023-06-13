#include <Arduino.h>
#include <EEPROM.h>
#include "whitelist.h"


// EEPROM functions
void writePinToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}

String readPinFromEEPROM(int addrOffset)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0';
  return String(data);
}


Whitelist::Whitelist(uint16_t addrWL, uint16_t addrWLCount, uint16_t addrMaster, uint16_t addrPin)
{
    _addrWL = addrWL;
    _addrWLCount = addrWLCount;
    _addrMaster = addrMaster;
    _addrPin = addrPin;

    Whitelist::init();
}

void Whitelist::getWhitelist()
{
    // Get Whitelist
    EEPROM.get(_addrWL, whitelistMember);

    for (uint8_t loop = 0; loop < whitelistMemberCount; loop++)
    {
        if (whitelistMember[loop] == 0xFFFFFFFF)
            whitelistMember[loop] = 0;
    }
}

void Whitelist::getWhitelistCount()
{
    // Get Whitelist count
    EEPROM.get(_addrWLCount, whitelistMemberCount);
    if (registeredMaster == 0xFF)
        registeredMaster = 0;
}

void Whitelist::getMaster()
{
    // Get Master
    EEPROM.get(_addrMaster, registeredMaster);
    if (registeredMaster == 0xFFFFFFFF)
        registeredMaster = 0;

    if (registeredMaster == 0)
    {
        for (uint8_t loop = 0; loop < whitelistMemberCount; loop++)
        {
            whitelistMember[loop] = 0;
        }

        whitelistMember[whitelistMemberCount] = 0;
    }
}

void Whitelist::getPin()
{
    registeredPin = readPinFromEEPROM(ADDRESS_KEYPAD_PIN);
    if(registeredPin >= "1000")
        pinIsRegistered = true;
    else
        pinIsRegistered = false;
}

void Whitelist::remove(uint32_t UID)
{
    for (uint8_t searchLoop = 0; searchLoop < whitelistMemberCount; searchLoop++)
    {
        if (whitelistMember[searchLoop] == UID)
        {
            // Deletes User
            whitelistMember[searchLoop] = 0;

            // Moves back the "NULL" value
            for (uint8_t moveLoop = searchLoop; moveLoop < whitelistMemberCount; moveLoop++)
                whitelistMember[moveLoop] = whitelistMember[moveLoop + 1];

            whitelistMember[whitelistMemberCount - 1] = 0x00000000;

            EEPROM.put(_addrWL, whitelistMember);

            whitelistMemberCount--;
            EEPROM.put(whitelistMemberCount, whitelistMemberCount);
            break;
        }
    }
}

bool Whitelist::add(uint32_t UID)
{
    if (UID == 0)
        return 0;

    for (uint8_t searchLoop = 0; searchLoop < WHITELIST_SIZE; searchLoop++)
    {
        if (whitelistMember[searchLoop] == UID)
        {
            return 0;
        }
    }

    for (uint8_t nextNull = 0; nextNull < WHITELIST_SIZE; nextNull++)
    {
        if (whitelistMember[nextNull] == 0 || whitelistMember[nextNull] == NULL)
        {
            whitelistMember[nextNull] = UID;
            EEPROM.put(_addrWL, whitelistMember);

            whitelistMemberCount++;
            EEPROM.put(_addrWLCount, whitelistMemberCount);
            return 1;
        }
    }

    // Signal list full reject
    return 0;
}

void Whitelist::reset()
{
    for (uint8_t deleteLoop = 0; deleteLoop < whitelistMemberCount; deleteLoop++)
    {
        whitelistMember[deleteLoop] = 0;
    }

    whitelistMember[whitelistMemberCount] = 0;

    EEPROM.put(_addrWL, whitelistMember);

    whitelistMemberCount = 0;
    EEPROM.put(_addrWLCount, whitelistMemberCount);
    return;
}

bool Whitelist::isMember(uint32_t UID)
{
    for (uint8_t searchLoop = 0; searchLoop < whitelistMemberCount; searchLoop++)
    {
        if (whitelistMember[searchLoop] == 0 || whitelistMember[searchLoop] == 0)
            return 0;
        if (whitelistMember[searchLoop] == UID)
            return 1;
    }
    return 0;
}

void Whitelist::masterSet(uint32_t UID)
{
    registeredMaster = UID;
    EEPROM.put(_addrMaster, registeredMaster);
}

void Whitelist::masterReset()
{
    registeredMaster = 0;
    EEPROM.put(_addrMaster, registeredMaster);
}

void Whitelist::pinSet(String newPin)
{
    writePinToEEPROM(ADDRESS_KEYPAD_PIN, newPin);
    registeredPin = newPin;
    pinIsRegistered = true;
}

void Whitelist::pinReset()
{
    registeredPin = "";
    writePinToEEPROM(ADDRESS_KEYPAD_PIN, registeredPin);
    pinIsRegistered = false;
}

bool Whitelist::pinCheck(String checkPin)
{
    if(checkPin == registeredPin)
        return 1;
    else
        return 0;
}

void Whitelist::init()
{
    Whitelist::getWhitelist();
    Whitelist::getWhitelistCount();
    Whitelist::getMaster();
    Whitelist::getPin();
}
