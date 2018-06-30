
#include "rtc.h"

char* RTC::ConvertWeekDay(uint8_t day) {
  switch(day) {
  case 0:
    return (char*)"Monday";
  case 1:
    return (char*)"Tuesday";
  case 2:
    return (char*)"Wednesday";
  case 3:
    return (char*)"Thursday";
  case 4:
    return (char*)"Friday";
  case 5:
    return (char*)"Saturday";
  case 6:
    return (char*)"Sunday";
  default:
    return (char*)"";
  }
}

uint8_t RTC::ConvertFromBCD(uint8_t val) {
  /* Function ConvertFromBCD and ConvertToBCD are taken from:
     https://rheingoldheavy.com/mcp7940-tutorial-02-setting-and-getting-time/
     in the full code section. */
  uint8_t msb = (val & 0b11110000) >> 4;
  uint8_t lsb = (val & 0b00001111);

  return ((msb * 10) + lsb);
}

uint8_t RTC::ConvertToBCD(uint8_t val) {
  return (val / 10) << 4 | (val % 10);
}

void RTC::Start() {
  TWI::Start();

  TWI::Write((RTC_ADDRESS << 1)); // In SLA_W (write) mode
  TWI::Write(0x00);
  TWI::Write(0x80); 

  TWI::Stop();
}

void RTC::ReadRegister(uint8_t address, uint8_t* buf) {
  TWI::Start();
  TWI::Write((RTC_ADDRESS << 1)); // In SLA_W (write) mode
  TWI::Write(address);
  TWI::Stop();

  TWI::Start();
  TWI::Write((RTC_ADDRESS << 1) + 0x01); // IN SLA_R (read) mode

  for(int i = 0; i < 7; ++i)
    buf[i] = TWI::Read();

  TWI::Stop();
}

void RTC::WriteTime(uint8_t seconds, uint8_t minutes, uint8_t hours,
                    uint8_t dayWeek, uint8_t day, uint8_t month, uint8_t year) {
  TWI::writeAddress = 0x00;
  TWI::Start();

  TWI::Write((RTC_ADDRESS << 1)); // In SLA_W (write) mode
  TWI::Write(0x00);

  TWI::Write(RTC::ConvertToBCD(seconds)); // seconds
  TWI::Write(RTC::ConvertToBCD(minutes)); // minutes 
  TWI::Write(RTC::ConvertToBCD(hours)); // hours

  TWI::Write(RTC::ConvertToBCD(dayWeek)); // day of the week
  TWI::Write(RTC::ConvertToBCD(day)); // day
  TWI::Write(RTC::ConvertToBCD(month)); // month
  TWI::Write(RTC::ConvertToBCD(year)); // year

  TWI::Stop();

  TWI::Start();

  TWI::Write(0xDE);
  TWI::Write(0x00);

  TWI::Write(0x23);

  TWI::Stop();
}

void RTC::SetCompileTime() {}

void RTC::Init() {
  TWI::Init();
  TWI::SetAddress(RTC_ADDRESS);

  uint8_t status = TWI::Status();

  /* Potential TODO: add proper status to TWI library. */
  if(status != 0xFF) {
    char errbuf[4];
    sprintf(errbuf, "%x", status);

    UART::Print("Current status: ");
    UART::Print(errbuf);
    UART::PutChar('\n');
  }

  RTC::SetCompileTime();
}

