// =============================================================================
// arduino-access-system | Dario Casciato
// =============================================================================

#include <Arduino.h>
#include "General.h"

namespace General
{
    Properties properties = {0};
    Whitelist whitelist(
        ADDRESS_WHITELIST,
        ADDRESS_WHITELISTCOUNT,
        ADDRESS_MASTER,
        ADDRESS_KEYPAD_PIN
    );
    Tag rfid;
    Signalisation signalize;

    uint8_t tagAvailableVal;
    EdgeDetection tagAvailable(&tagAvailableVal);
} // namespace General