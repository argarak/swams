
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

/* Array should be as follows:

  [0]: seconds
  [1]: minutes
  [2]: hours
  [3]: day of the week
  [4]: day
  [5]: month
  [6]: year */
void RTC::WriteTime(int d[7]) {
  TWI::writeAddress = 0x00;
  TWI::Start();

  TWI::Write((RTC_ADDRESS << 1)); // In SLA_W (write) mode
  TWI::Write(0x00);

  TWI::Write(RTC::ConvertToBCD(d[0])); // seconds
  TWI::Write(RTC::ConvertToBCD(d[1])); // minutes 
  TWI::Write(RTC::ConvertToBCD(d[2])); // hours

  TWI::Write(RTC::ConvertToBCD(d[3])); // day of the week
  TWI::Write(RTC::ConvertToBCD(d[4])); // day
  TWI::Write(RTC::ConvertToBCD(d[5])); // month
  TWI::Write(RTC::ConvertToBCD(d[6])); // year

  TWI::Stop();
}

void RTC::GenerateArrayFromEEPROM(int d[7]) {
  d[0] = EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, SECOND_ELEMENT);
  d[1] = EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, MINUTE_ELEMENT);
  d[2] = EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, HOUR_ELEMENT);
  d[3] = EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, DAYWEEK_ELEMENT);
  d[4] = EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, DAY_ELEMENT);
  d[5] = EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, MONTH_ELEMENT);
  d[6] = EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, YEAR_ELEMENT);
}

void RTC::UpdateFromEEPROM() {
  
}

/* Returns true if first date is greater than second date */
bool RTC::CompareDates(uint8_t a[7], uint8_t b[7]) {

  /* Skipping index 3 as that's the week day element */

  if(a[0] > b[0]) return true;
  if(a[1] > b[1]) return true;
  if(a[2] > b[2]) return true;
  if(a[4] > b[4]) return true;
  if(a[5] > b[5]) return true;
  if(a[6] > b[6]) return true;
  return false;
}

void RTC::SetCompileTime() {
  int cd[7];

  char monthBuf[10];

  static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

  sscanf(__DATE__, "%s %d 20%d", monthBuf, &cd[4], &cd[6]);
  sscanf(__TIME__, "%d:%d:%d", &cd[2], &cd[1], &cd[0]);

  char dayBuf[10];

  sscanf(__TIMESTAMP__, "%s", dayBuf);

  static const char day_names[] = "MonTueWedThuFriSatSun";

  cd[5] = (strstr(month_names, monthBuf) - month_names) / 3 + 1;
  cd[3] = (strstr(day_names, dayBuf) - day_names) / 3;

  int ed[7];
  RTC::GenerateArrayFromEEPROM(ed);

  RTC::WriteTime(ed);
}

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

  //RTC::WriteTime(45, 47, 20, 7, 1, 7, 18);

  RTC::SetCompileTime();
}

