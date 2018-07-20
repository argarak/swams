
#ifndef _H_EEPROM
#define _H_EEPROM

#include <avr/io.h>
#include <avr/eeprom.h>
#include "../../macros.h"

#define RTC_DATE_ADDRESS     0
#define LIGHT_START_ADDRESS  1
#define LIGHT_STOP_ADDRESS   2

#define SECOND_ELEMENT       0
#define MINUTE_ELEMENT       1
#define HOUR_ELEMENT         2
#define DAYWEEK_ELEMENT      3
#define DAY_ELEMENT          4
#define MONTH_ELEMENT        5
#define YEAR_ELEMENT         6

#define MAX_TEMP_ELEMENT     0
#define MIN_TEMP_ELEMENT     1
#define REG_TEMP_ELEMENT     2
#define THRESHOLD_ELEMENT    3

namespace EEPROM {
  void SaveDate(int d[7]);

  uint8_t RetrieveDateElement(uint8_t timeAddress, uint8_t elementAddress);

  void SetTemps(uint8_t max, uint8_t min, uint8_t reg, uint8_t threshold);

  uint8_t RetrieveTempElement(uint8_t addr);

  void SaveTime(uint8_t timeAddress, uint8_t seconds,
                uint8_t minutes, uint8_t hours);
}

#endif
