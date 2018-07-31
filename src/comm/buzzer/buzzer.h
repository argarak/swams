#ifndef _H_BUZZER
#define _H_BUZZER

#include <avr/io.h>
#include <inttypes.h>

#include <util/delay.h>

#include "../../macros.h"

#define BUZZ_TEMP_HIGH 1,2,1
#define BUZZ_TEMP_LOW  2,1,2
#define BUZZ_TEST_OK   1,1,1

namespace Buzzer {
  void Init();
  void Beep(uint8_t len1, uint8_t len2, uint8_t len3);
}

#endif
