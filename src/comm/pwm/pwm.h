
#ifndef _H_PWM
#define _H_PWM

#include <avr/io.h>
#include "../../macros.h"

namespace PWM {
  void Init(uint16_t dc);
  void SetDutyCycle(uint16_t dc);
}

#endif
