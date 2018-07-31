
#include "monitor.h"

void Monitor::Update() {
  /* Check if temperature is too high/low */

  uint8_t regTemp = EEPROM::RetrieveTempElement(REG_TEMP_ELEMENT);
  uint8_t threshold = EEPROM::RetrieveTempElement(THRESHOLD_ELEMENT);

  if((DS18B20::ReadTemp() - threshold) > (regTemp * 10)) {
    io_set_high(PORT(D,7), BIT(D,7));
  }

  if((DS18B20::ReadTemp() + threshold) < (regTemp * 10)) {
    io_set_low(PORT(D,7), BIT(D,7));
  }

  /* Check if LEDs should switch on */

  

  /* Check if water level too high/low */
}
