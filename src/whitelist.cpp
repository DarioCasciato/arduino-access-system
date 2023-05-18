#include <Arduino.h>
#include <EEPROM.h>
#include "whitelist.h"

Whitelist::Whitelist(uint16_t addrWL, uint16_t addrWLCount, uint16_t addrMaster)
{
    _addrWL = addrWL;
    _addrWLCount = addrWLCount;
    _addrMaster = addrMaster;

    Whitelist::init();
}

void Whitelist::init()
{
    Whitelist::getWhitelist();
    Whitelist::getWhitelistCount();
    Whitelist::getMaster();
}

void Whitelist::getWhitelist()
{
    // Get Whitelist
    EEPROM.get(_addrWL, whitelistMember);

    for (uint8_t loop = 0; loop < _addrWLCount; loop++)
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
        for (uint8_t loop = 0; loop < _addrWLCount; loop++)
        {
            whitelistMember[loop] = 0;
        }

        whitelistMember[_addrWLCount] = 0;
    }
}

void Whitelist::remove(uint32_t UID)
{
    for (unsigned char searchLoop = 0; searchLoop < _addrWLCount; searchLoop++)
    {
        if (whitelistMember[searchLoop] == UID)
        {
            // Deletes User
            whitelistMember[searchLoop] = 0;

            // Moves back the "NULL" value
            for (uint8_t moveLoop = searchLoop; moveLoop < _addrWLCount; moveLoop++)
                whitelistMember[moveLoop] = whitelistMember[moveLoop + 1];

            whitelistMember[_addrWLCount - 1] = 0x00000000;

            EEPROM.put(_addrWL, whitelistMember);

            whitelistMemberCount--;
            EEPROM.put(_addrWLCount, whitelistMemberCount);
            break;
        }
    }
}

bool Whitelist::add(uint32_t UID)
{
    if (UID == 0)
        return 0;

    for (unsigned char searchLoop = 0; searchLoop < _addrWLCount; searchLoop++)
    {
        if (whitelistMember[searchLoop] == UID)
        {
            return 0;
        }
    }

    for (unsigned char nextNull = 0; nextNull < _addrWLCount; nextNull++)
    {
        if (whitelistMember[nextNull] == 0 || whitelistMember[nextNull] == 0)
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
    for (unsigned char deleteLoop = 0; deleteLoop < _addrWLCount; deleteLoop++)
    {
        whitelistMember[deleteLoop] = 0;
    }

    whitelistMember[_addrWLCount] = 0;

    EEPROM.put(_addrWL, whitelistMember);

    whitelistMemberCount = 0;
    EEPROM.put(_addrWLCount, whitelistMemberCount);
    return;
}

bool Whitelist::isMember(uint32_t UID)
{
    for (unsigned char searchLoop = 0; searchLoop < _addrWLCount; searchLoop++)
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
