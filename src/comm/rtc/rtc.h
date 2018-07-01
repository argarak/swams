#ifndef _H_RTC
#define _H_RTC

#include <avr/io.h>
#include <stdio.h>
#include <string.h>

#include "../../macros.h"
#include "../twi/twi.h"
#include "../uart/uart.h"

#define RTC_ADDRESS       0x6F

namespace RTC {
  char* ConvertWeekDay(uint8_t day);

  uint8_t ConvertFromBCD(uint8_t val);
  uint8_t ConvertToBCD(uint8_t val);

  void WriteTime(uint8_t seconds, uint8_t minutes, uint8_t hours,
                 uint8_t dayWeek, uint8_t day, uint8_t month, uint8_t year);
  void SetCompileTime();

  void Start();
  void ReadRegister(uint8_t address, uint8_t* buf);
  void Init();
}

#endif
