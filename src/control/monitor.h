#ifndef _H_MONITOR
#define _H_MONITOR

#include <avr/io.h>

#include "../comm/uart/uart.h"
#include "../comm/eeprom/eeprom.h"
#include "../comm/pwm/pwm.h"
#include "../comm/ds18b20/temp.h"
#include "../comm/rtc/rtc.h"

#include "../macros.h"

namespace Monitor {
  void Update();
}

#endif
