#ifndef _H_RTC
#define _H_RTC

#include <avr/io.h>
#include <stdio.h>

#include "../../macros.h"
#include "../twi/twi.h"
#include "../uart/uart.h"

#define RTC_ADDRESS       0x6F

namespace RTC {
  void Start();
  uint8_t ReadRegister(uint8_t address);
  void Init();
}

#endif
