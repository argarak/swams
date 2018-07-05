
/* Bit-bang library for interfacing with OneWire devices.
   Useful resource: http://karve.in/?p=1408 */

#include "onewire.h"

void OneWire::WriteZero() {
  io_output_mode(DDR(ONEWIRE_DATA), PIN(ONEWIRE_DATA));
  io_set_low(PORT(ONEWIRE_DATA), PIN(ONEWIRE_DATA));

  _delay_us(60);

  io_input_mode(DDR(ONEWIRE_DATA), PIN(ONEWIRE_DATA));

  _delay_us(1);
}

void OneWire::WriteOne() {
  io_output_mode(DDR(ONEWIRE_DATA), PIN(ONEWIRE_DATA));
  io_set_low(PORT(ONEWIRE_DATA), PIN(ONEWIRE_DATA));

  _delay_us(5);

  io_input_mode(DDR(ONEWIRE_DATA), PIN(ONEWIRE_DATA));

  _delay_us(55);
  _delay_us(1);
}

void OneWire::WriteByte(uint8_t byte) {
  for(uint8_t i = 0; i < 8; ++i) {
    if(byte & _BV(i)) {
      /* Byte is 1 */
      OneWire::WriteOne();
    } else {
      /* Byte is 0 */
      OneWire::WriteZero();
    }
  }
}

uint8_t OneWire::Read() {
  io_output_mode(DDR(ONEWIRE_DATA), PIN(ONEWIRE_DATA));
  io_set_low(PORT(ONEWIRE_DATA), PIN(ONEWIRE_DATA));

  _delay_us(5);

  io_input_mode(DDR(ONEWIRE_DATA), PIN(ONEWIRE_DATA));

  _delay_us(10);

  if(io_input_high(IPIN(ONEWIRE_DATA), BIT(ONEWIRE_DATA))) {
    _delay_us(45);
    return 1;
  } else {
    _delay_us(45);
    return 0;
  }
}

uint16_t OneWire::ReadByte() {
  uint16_t data;

  for(uint8_t i = 0; i < 16; ++i) {
    if(OneWire::Read()) data = (data & _BV(i));
  }

  return data;
}

uint8_t OneWire::Reset() {
  /* Set mode to output and pull data line low for 480us. */
  io_output_mode(DDR(ONEWIRE_DATA), PIN(ONEWIRE_DATA));
  io_set_low(PORT(ONEWIRE_DATA), PIN(ONEWIRE_DATA));

  _delay_us(480);

  /* Set mode to input and wait 80us, checking if slave device is present. */
  io_input_mode(DDR(ONEWIRE_DATA), PIN(ONEWIRE_DATA));

  for(uint8_t i = 0; i < 80; ++i) {
    /* Check if data line is pulled low... */
    if(!io_input_high(IPIN(ONEWIRE_DATA), BIT(ONEWIRE_DATA))) {
      /* Device found, no errors. */
      _delay_us(480);
      return 0;
    }

    _delay_us(1);
  }

  /* No message from slave device, error! */
  return 1;
}

void OneWire::Init() {
  if(OneWire::Reset() == 1) {
    UART::Print("Error, OneWire failed!\n");
  }
}
