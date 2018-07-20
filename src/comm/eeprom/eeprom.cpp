
#include "eeprom.h"

/* Define EEPROM addresses for each element */

/* RTC date elements */
#define EE_RTC_SEC 0
#define EE_RTC_MIN 1
#define EE_RTC_HR  2
#define EE_RTC_WKD 3
#define EE_RTC_DAY 4
#define EE_RTC_MTH 5
#define EE_RTC_YR  6

/* Light start time elements */
#define EE_START_SEC 7
#define EE_START_MIN 8
#define EE_START_HR  9

/* Light stop time elements */
#define EE_STOP_SEC  10
#define EE_STOP_MIN  11
#define EE_STOP_HR   12

/* Temperature elements */
#define EE_TEMP_MIN  13      /* Minimum temperature */
#define EE_TEMP_MAX  14      /* Maximum temperature */
#define EE_TEMP_REG  15      /* Regulated temperature */
#define EE_TEMP_TRH  16      /* Threshold */

void EEPROM::SaveDate(int d[7]) {

  /*             |  Pointer to Address    | Value     | */
  eeprom_write_byte((uint8_t*)EE_RTC_SEC,  d[0]);
  eeprom_write_byte((uint8_t*)EE_RTC_MIN,  d[1]);
  eeprom_write_byte((uint8_t*)EE_RTC_HR,   d[2]);
  eeprom_write_byte((uint8_t*)EE_RTC_WKD,  d[3]);
  eeprom_write_byte((uint8_t*)EE_RTC_DAY,  d[4]);
  eeprom_write_byte((uint8_t*)EE_RTC_MTH,  d[5]);
  eeprom_write_byte((uint8_t*)EE_RTC_YR,   d[6]);
}

uint8_t EEPROM::RetrieveDateElement(uint8_t timeAddress,
                                    uint8_t elementAddress) {

  switch(timeAddress) {
  case RTC_DATE_ADDRESS:
    switch(elementAddress) {
    case SECOND_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_RTC_SEC);
      
    case MINUTE_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_RTC_MIN);
      
    case HOUR_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_RTC_HR);
      
    case DAYWEEK_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_RTC_WKD);
      
    case DAY_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_RTC_DAY);
      
    case MONTH_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_RTC_MTH);
      
    case YEAR_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_RTC_YR);

    default:
      return 0;
    }
    break;

  case LIGHT_START_ADDRESS:
    switch(elementAddress) {
    case SECOND_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_START_SEC);

    case MINUTE_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_START_MIN);

    case HOUR_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_START_HR);

    default:
      return 0;
    }
    break;

  case LIGHT_STOP_ADDRESS:
    switch(elementAddress) {
    case SECOND_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_STOP_SEC);

    case MINUTE_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_STOP_MIN);

    case HOUR_ELEMENT:
      return eeprom_read_byte((uint8_t*)EE_STOP_HR);

    default:
      return 0;
    }
    break;

  default:
    return 0;
  }
}

void EEPROM::SetTemps(uint8_t max, uint8_t min,
                      uint8_t reg, uint8_t threshold) {

  eeprom_write_byte((uint8_t*)EE_TEMP_MAX, max);
  eeprom_write_byte((uint8_t*)EE_TEMP_MIN, min);
  eeprom_write_byte((uint8_t*)EE_TEMP_REG, reg);
  eeprom_write_byte((uint8_t*)EE_TEMP_TRH, threshold);
}

uint8_t EEPROM::RetrieveTempElement(uint8_t addr) {
  switch(addr) {
  case MAX_TEMP_ELEMENT:
    return eeprom_read_byte((uint8_t*)EE_TEMP_MAX);

  case MIN_TEMP_ELEMENT:
    return eeprom_read_byte((uint8_t*)EE_TEMP_MIN);

  case REG_TEMP_ELEMENT:
    return eeprom_read_byte((uint8_t*)EE_TEMP_REG);

  case THRESHOLD_ELEMENT:
    return eeprom_read_byte((uint8_t*)EE_TEMP_TRH);

  default:
    return 0;
  }
}

void EEPROM::SaveTime(uint8_t timeAddress, uint8_t seconds,
                      uint8_t minutes, uint8_t hours) {
  switch(timeAddress) {
  case RTC_DATE_ADDRESS:
    eeprom_write_byte((uint8_t*)EE_RTC_SEC, seconds);
    eeprom_write_byte((uint8_t*)EE_RTC_MIN, minutes);
    eeprom_write_byte((uint8_t*)EE_RTC_HR,  hours);

  case LIGHT_START_ADDRESS:
    eeprom_write_byte((uint8_t*)EE_START_SEC, seconds);
    eeprom_write_byte((uint8_t*)EE_START_MIN, minutes);
    eeprom_write_byte((uint8_t*)EE_START_HR,  hours);

  case LIGHT_STOP_ADDRESS:
    eeprom_write_byte((uint8_t*)EE_STOP_SEC, seconds);
    eeprom_write_byte((uint8_t*)EE_STOP_MIN, minutes);
    eeprom_write_byte((uint8_t*)EE_STOP_HR,  hours);
  }
}
