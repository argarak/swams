
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

    uint8_t timeBuf[7];
    RTC::ReadRegister(0x00, timeBuf);

    for(int i = 0; i < 7; ++i)
      timeBuf[i] = RTC::ConvertFromBCD(timeBuf[i]);

    char secbuf[64];
    sprintf(secbuf, "Time: %i:%i:%02i | Date: %i %i/%i/%i\n",
            timeBuf[2],
            timeBuf[1],
            timeBuf[0] - 80,
            timeBuf[3],
            timeBuf[4],
            timeBuf[5],
            timeBuf[6]);

    UART::Print(secbuf);

    _delay_ms(500);

    PORTB &= ~_BV(PB0);
    _delay_ms(500);
  }
}
