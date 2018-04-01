
#include "src/macros.h"
#include "src/comm/uart/uart.h"
#include "util/delay.h"

int main(void) {
  UART::Init();

  DDRB |= _BV(DDB0);

  while (1) {
    PORTB |= _BV(PB0);
    UART::Print("hello world!\n");
    _delay_ms(500);

    PORTB &= ~_BV(PB0);
    _delay_ms(500);
  }
}
