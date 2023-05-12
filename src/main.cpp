// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "hardware.h"
#include "configurations.h"
#include "whitelist.h"
#include "rfid_utility.h"
#include "signalisation.h"
#include "../lib/EdgeDetection.h"

Whitelist whitelist(ADDRESS_WHITELIST, ADDRESS_WHITELISTCOUNT, ADDRESS_MASTER);
Tag rfid();

void setup()
{
  Hardware::init();
  whitelist.init();
}

void loop()
{
  for (;;)
  {
  }
}