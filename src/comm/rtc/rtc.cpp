
#include "rtc.h"

void RTC::Start() {
  TWI::Start();

  TWI::Write((RTC_ADDRESS << 1)); // In SLA_W (write) mode
  TWI::Write(0x00);
  TWI::Write(0x80); 

  TWI::Stop();

  UART::Print("initted!\n");
}

uint8_t RTC::ReadRegister(uint8_t address) {
  TWI::Start();
  TWI::Write((RTC_ADDRESS << 1)); // In SLA_W (write) mode
  TWI::Write(address);
  TWI::Stop();

  uint8_t buf[7];

  TWI::Start();
  TWI::Write((RTC_ADDRESS << 1) + 0x01); // IN SLA_R (read) mode

  for(int i = 0; i < 7; ++i)
    buf[i] = TWI::Read();

  TWI::Stop();

  return buf[0];
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

