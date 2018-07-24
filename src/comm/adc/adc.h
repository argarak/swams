
#ifndef _H_ADC
#define _H_ADC

#include <avr/io.h>
#include "../../macros.h"

namespace ATDC {
  void Init();
  uint16_t ReadValue();
}

#endif
