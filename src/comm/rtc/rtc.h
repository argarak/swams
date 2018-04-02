#ifndef _H_RTC
#define _H_RTC

#include <avr/io.h>
#include "../../macros.h"
#include "../twi/twi.h"

#define PIN_SDA B,5
#define PIN_SCL B,7

namespace RTC {
  void Init();
}

#endif
