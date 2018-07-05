
#include "temp.h"

/* Output value is in integer format and not float/double as I was having
   issues with this data type. However, since this value will be sent via a
   Bluetooth application, the conversion to degrees Celsius will be performed
   client-side (multiply by 0.0625). */
uint16_t DS18B20::ReadTemp() {
  OneWire::Init();

  OneWire::WriteByte(0xCC);
  OneWire::WriteByte(0x44);

  _delay_us(750);

  OneWire::Reset();

  OneWire::WriteByte(0xCC);
  OneWire::WriteByte(0xBE);

  uint16_t data = OneWire::ReadByte();

  return data;
}
