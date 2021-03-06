
#include "src/macros.h"
#include "src/comm/uart/uart.h"
#include "src/comm/rtc/rtc.h"
#include "src/comm/eeprom/eeprom.h"
#include "src/comm/ds18b20/temp.h"
#include "src/comm/pwm/pwm.h"
#include "src/comm/adc/adc.h"

#include "util/delay.h"

#include "src/control/command.h"
#include "src/control/monitor.h"

#include <stdio.h>
#include <avr/interrupt.h>

int main(void) {
  UART::Init();

  RTC::Init();
  RTC::Start();

  ATDC::Init();

  EEPROM::SetTemps(40, 20, 38, 32);

  Buzzer::Init();

  DDRD |= _BV(DDD7);
  PORTD |= _BV(PD7);

  io_set_high(PORT(D,7), BIT(D,7));

  _delay_ms(500);

  io_set_low(PORT(D,7), BIT(D,7));

  Buzzer::Beep(BUZZ_TEST_OK);

  while(1) {
    uint8_t timeBuf[7];
    RTC::ReadRegister(0x00, timeBuf);

    for(int i = 0; i < 7; ++i) {
      timeBuf[i] = RTC::ConvertFromBCD(timeBuf[i]);
    }

    char buf[64];
    sprintf(buf, "Time: %i:%i:%02i | Date: %s %i/%i/%i\n",
            timeBuf[2],
            timeBuf[1],
            timeBuf[0] - 80,
            RTC::ConvertWeekDay(timeBuf[3] - 20),
            timeBuf[4],
            timeBuf[5],
            timeBuf[6]);

    UART::Print(buf);

    sprintf(buf, "Temp: %d\n", DS18B20::ReadTemp());
    UART::Print(buf);

    sprintf(buf, "ADC: %i\n", ATDC::ReadValue());
    UART::Print(buf);

    _delay_ms(1000);

    /* TODO: check for method to enable temp/led function without
       pinging uart */
    Command::Listen();

    Monitor::Update();
  }

  // PWM::Init(0);

  // uint16_t a = 0;

  // while(1) {
  //   if(a < 65534) a++;
  //   else a = 0;

  //   PWM::SetDutyCycle(a);

  //   _delay_us(500);
  // }

  // EEPROM::SetTemps(50, 12, 25, 2);
  // EEPROM::SaveTime(LIGHT_START_ADDRESS, 12, 12, 12);
  // EEPROM::SaveTime(LIGHT_STOP_ADDRESS, 10, 10, 10);

  // while(1) {
  //   char datebuf[64];
  //   sprintf(datebuf, "RTC:: Time: %i:%i:%02i | Date: %s %i/%i/%i\n",
  //           EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, HOUR_ELEMENT),
  //           EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, MINUTE_ELEMENT),
  //           EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, SECOND_ELEMENT),
  //           RTC::ConvertWeekDay(EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS,
  //                                                           DAYWEEK_ELEMENT)),
  //           EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, DAY_ELEMENT),
  //           EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, MONTH_ELEMENT),
  //           EEPROM::RetrieveDateElement(RTC_DATE_ADDRESS, YEAR_ELEMENT));

  //   char startbuf[64];
  //   sprintf(startbuf, "Start:: Time: %i:%i:%02i\n",
  //           EEPROM::RetrieveDateElement(LIGHT_START_ADDRESS, HOUR_ELEMENT),
  //           EEPROM::RetrieveDateElement(LIGHT_START_ADDRESS, MINUTE_ELEMENT),
  //           EEPROM::RetrieveDateElement(LIGHT_START_ADDRESS, SECOND_ELEMENT));

  //   char stopbuf[64];
  //   sprintf(stopbuf, "Stop: Time: %i:%i:%02i\n",
  //           EEPROM::RetrieveDateElement(LIGHT_STOP_ADDRESS, HOUR_ELEMENT),
  //           EEPROM::RetrieveDateElement(LIGHT_STOP_ADDRESS, MINUTE_ELEMENT),
  //           EEPROM::RetrieveDateElement(LIGHT_STOP_ADDRESS, SECOND_ELEMENT));

  //   char tempbuf[64];
  //   sprintf(tempbuf, "Temps:: Max: %i, Min: %i, Reg: %i, Threshold: %i\n",
  //           EEPROM::RetrieveTempElement(MAX_TEMP_ELEMENT),
  //           EEPROM::RetrieveTempElement(MIN_TEMP_ELEMENT),
  //           EEPROM::RetrieveTempElement(REG_TEMP_ELEMENT),
  //           EEPROM::RetrieveTempElement(THRESHOLD_ELEMENT));

  //   UART::Print(datebuf);
  //   UART::Print(startbuf);
  //   UART::Print(stopbuf);
  //   UART::Print(tempbuf);

  //   _delay_ms(10000);
  // }
}
