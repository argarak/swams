
#include "uart.h"

// void UART::Init() {

// #if USE_2X
//   UCSR0A |= (1 << U2X0);
// #else
//   UCSR0A &= ~(1 << U2X0);
// #endif

//   DDRD |= _BV(1);
//   UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
//   UCSR0B = _BV(RXEN0) | _BV(TXEN0);
// }

void UART::Init() {
#define BAUD 19200
#include <util/setbaud.h>
  /* Set baud rate */
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

  /* Enable receiver and transmitter */
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);  
}

bool UART::IsAvailable() {
  if((UCSR0A & _BV(UDRE0)) == 0)
    return false;
  return true;
}

uint16_t UART::Strlen(const char* str) {
  uint16_t len;
  for(len = 0; str[len]; len++);
  return len;
}

void UART::Print(const char* data) {
  for(int i = 0; i < UART::Strlen(data); i++) {
    while(!UART::IsAvailable())
      ;
    UDR0 = data[i];
  }
}

void UART::PutChar(unsigned char data) {
  while(!UART::IsAvailable())
    ;
  UDR0 = (int)data;
}

uint8_t UART::GetChar() {
  //loop_until_bit_is_set(UCSR0A, RXC0);
  while(!(UCSR0A & (1 << RXC0)))
    ;
  return UDR0;
}

char* UART::ReadString() {
  char* buf = (char*)malloc(255);

  buf[0] = '\0';

  uint8_t i = 0;
  char b = '\0';

  do {
    do {
      b = UART::GetChar();
      break;

    } while(1);

    buf[i] = b;
    i++;

  } while(b != '\n' && b != '\r' && b != '\0');

  buf[i] = '\0';

  // remember to free()!
  return buf;
}
