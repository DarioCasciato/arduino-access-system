// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "hardware.h"
#include "configurations.h"
#include "whitelist.h"
#include "rfid_utility.h"
#include "signalisation.h"
#include "EdgeDetection.h"


Whitelist whitelist(ADDRESS_WHITELIST, ADDRESS_WHITELISTCOUNT, ADDRESS_MASTER);
Tag rfid;
Signalisation signalize;

uint8_t tagAvailableVal;
EdgeDetection tagAvailable(&tagAvailableVal);


void refreshData();


void setup()
{
  Hardware::init();
  whitelist.init();
}

void loop()
{

  for (;;)
  {
    refreshData();
  }
}


void refreshData()
{
  tagAvailableVal = rfid.tagPresent();
  EdgeDetection::updateEdges();
}
