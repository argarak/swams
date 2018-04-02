
#include "rtc.h"

void RTC::Init() {
  // Setting TWI registers to clock frequency of 400kHz
  TWSR = 0x00;
  TWBR = 0x0C;

  TWCR = (1 << TWEN);
}
