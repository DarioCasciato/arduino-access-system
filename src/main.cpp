// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "hardware.h"
#include "configurations.h"
#include "state.h"
#include "General.h"


void refreshData();

//------------------------------------------------------------------------------

void setup()
{
  Serial.begin(9600);

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

//------------------------------------------------------------------------------

void refreshData()
{
  General::tagAvailableVal = General::rfid.tagPresent();
  EdgeDetection::updateEdges();

  General::properties.isMaster = General::rfid.checkMaster();

  if(General::tagAvailable.getEdgePos())
  {
    General::properties.uid = General::rfid.getUID();
  }


  for (uint8_t i = 0; i < 6; i++)
    Hardware::key.keyByte[i] = 0xFF;
}
