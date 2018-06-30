#ifndef _H_TWI
#define _H_TWI

#include <stdlib.h>
#include <inttypes.h>
#include "../../macros.h"

#define TWI_NOT_COMPLETE ((TWCR & (1 << TWINT)) == 0)

#define SCL_PIN C,5
#define SDA_PIN C,4

/* Taken from TWI Arduino library. */
#ifndef TWI_BUFFER_LENGTH
#define TWI_BUFFER_LENGTH 32
#endif

namespace TWI {
  static volatile uint8_t twiBuffer[TWI_BUFFER_LENGTH];
  static volatile uint8_t twiBufferLength;

  extern volatile uint8_t writeAddress;

  void Init();
  void SetAddress(uint8_t address);

  void Start();
  void Stop();

  void Write(uint8_t data);
  uint8_t Read();

  uint8_t Status();
}

#endif
