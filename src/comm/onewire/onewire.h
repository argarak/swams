
#ifndef _H_ONEWIRE
#define _H_ONEWIRE

#include <avr/io.h>
#include <util/delay.h>

#include "../../macros.h"
#include "../uart/uart.h"
#include "../../../config.h"

namespace OneWire {
  void WriteZero();
  void WriteOne();
  void WriteByte(uint8_t byte);

  uint8_t Read();
  uint16_t ReadByte();

  uint8_t Reset();

  void Init();
}

#endif
