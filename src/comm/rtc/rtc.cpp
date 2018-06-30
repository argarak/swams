
#include "rtc.h"

void RTC::Start() {
  TWI::SetAddress(RTC_ADDRESS);

  TWI::Start();

  TWI::Write(0x00);
  TWI::Write(0x80); 

  TWI::Stop();

  UART::Print("initted!\n");
}

uint8_t RTC::ReadRegister(uint8_t address) {
  TWI::SetAddress(RTC_ADDRESS);

  TWI::Start();
  TWI::Write(address);

  uint8_t value = TWI::Read();
  TWI::Stop();

  return value;
}

void RTC::Init() {
  TWI::Init();
  TWI::SetAddress(RTC_ADDRESS);

  uint8_t status = TWI::Status();

  if(status != 0xFF) {
    char errbuf[4];
    sprintf(errbuf, "%x", status);

    UART::Print("Current status: ");
    UART::Print(errbuf);
    UART::PutChar('\n');
  }

  UART::Print("Probably successful!\n");

  TWI::writeAddress = 0x00;
  TWI::Start();

  TWI::Write(0xDE);

  TWI::Write(0x01);
  TWI::Write(0x45);
  TWI::Write(0x11);

  TWI::Write(0x02);
  TWI::Write(0x14);
  TWI::Write(0x08);
  TWI::Write(0x12);

  TWI::Stop();

  TWI::Start();

  TWI::Write(0xDE);
  TWI::Write(0x00);

  TWI::Write(0x23);

  TWI::Stop();

  UART::Print("Some sort of time value was written!\n");
}

