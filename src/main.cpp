// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "hardware.h"
#include "configurations.h"
#include "state.h"


void refreshData();


void setup()
{
  Hardware::init();
  General::whitelist.init();
}

void loop()
{

  for (;;)
  {
    refreshData();

    State::stateDriver();
  }
}


void refreshData()
{
  General::tagAvailableVal = General::rfid.tagPresent();
  EdgeDetection::updateEdges();
}
