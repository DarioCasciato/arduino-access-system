// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "General.h"

namespace General
{
    badgePresent badge = {0};
    Whitelist whitelist(ADDRESS_WHITELIST, ADDRESS_WHITELISTCOUNT, ADDRESS_MASTER);
    Tag rfid;
    Signalisation signalize;

    uint8_t tagAvailableVal;
    EdgeDetection tagAvailable(&tagAvailableVal);
} // namespace General