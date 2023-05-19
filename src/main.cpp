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

    delay(10);
  }
}


void refreshData()
{
  General::tagAvailableVal = General::rfid.tagPresent();
  EdgeDetection::updateEdges();

  for (uint8_t i = 0; i < 6; i++)
    Hardware::key.keyByte[i] = 0xFF;
}
