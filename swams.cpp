
#include "src/macros.h"
#include "src/comm/uart/uart.h"
#include "src/comm/rtc/rtc.h"
#include "util/delay.h"

#include <stdio.h>

int main(void) {
  UART::Init();
  RTC::Init();
  RTC::Start();

  DDRB |= _BV(DDB0);

  while (1) {
    PORTB |= _BV(PB0);

    uint8_t seconds;
    seconds = RTC::ReadRegister(0x00);

    char secbuf[16];
    sprintf(secbuf, "%x\n", seconds);

    UART::Print("Current seconds: ");
    UART::Print(secbuf);

    _delay_ms(500);

    PORTB &= ~_BV(PB0);
    _delay_ms(500);
  }
}
