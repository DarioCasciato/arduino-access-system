// =============================================================================
// arduino-access-system | Dario Casciato
// =============================================================================

#include <Arduino.h>
#include <EEPROM.h>
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
  EEPROM.begin();
  General::whitelist.init();

  State::onStart();
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
  // RFID Properties
  General::tagAvailableVal = General::rfid.tagPresent();
  EdgeDetection::updateEdges();

  if(General::rfid.checkMaster())
  {
    General::properties.isMaster = 1;
  }

  if(General::tagAvailable.getEdgePos())
  {
    General::properties.uid = General::rfid.getUID();
  }

  if ((!General::tagAvailable.getEdgeNeg()) && (!General::tagAvailable.getActState()))
  {
    General::properties.isMaster = 0;
  }

  for (uint8_t i = 0; i < 6; i++)
    Hardware::key.keyByte[i] = 0xFF;

  // Keypad
  General::keypad_key = Hardware::keypad.getKey();

  if(Hardware::keypad.getState() == KeyState::RELEASED)
  {
    General::keypad_key = 0;
  }
}
