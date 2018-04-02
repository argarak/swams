#ifndef _H_TWI
#define _H_TWI

#include <avr/io.h>
#include <stdlib.h>

namespace TWI {
  void Init();

  void Start();
  void Stop();

  void Write(uint8_t data);
  uint8_t Read();

  uint8_t Status();
}

#endif
