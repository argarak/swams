
#include "temp.h"

void DS18B20::Init() {
  OneWire::Init();

  OneWire::WriteByte(0xCC);
  OneWire::WriteByte(0x44);

  _delay_us(750);

  OneWire::Reset();

  OneWire::WriteByte(0xCC);
  OneWire::WriteByte(0xBE);

  uint16_t data = OneWire::ReadByte();

  char buf[64];

  sprintf(buf, "temp: 0x%04x\n", data);

  UART::Print(buf);
}
