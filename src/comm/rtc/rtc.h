#ifndef _H_RTC
#define _H_RTC

#include <avr/io.h>
#include <stdio.h>
#include <string.h>

#include "../../macros.h"
#include "../twi/twi.h"
#include "../uart/uart.h"
#include "../eeprom/eeprom.h"

#define RTC_ADDRESS       0x6F

namespace RTC {
  char* ConvertWeekDay(uint8_t day);

  uint8_t ConvertFromBCD(uint8_t val);
  uint8_t ConvertToBCD(uint8_t val);

  void WriteTime(int d[7]);
  void GenerateArrayFromEEPROM(int d[7]);

  void UpdateFromEEPROM();
  bool CompareDates(uint8_t a[7], uint8_t b[7]);
  void SetCompileTime();

  void Start();
  void ReadRegister(uint8_t address, uint8_t* buf);
  void Init();
}

#endif
