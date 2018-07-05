
#ifndef _H_DS18B20
#define _H_DS18B20

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "../../macros.h"

#include "../onewire/onewire.h"

namespace DS18B20 {
  void Init();
  //  uint8_t ReadTemp();
}

#endif
