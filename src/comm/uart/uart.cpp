
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
  UBRRH = UBRRH_VALUE;
  UBRRL = UBRRL_VALUE;

  /* Enable receiver and transmitter */
  UCSRB = (1 << RXEN) | (1 << TXEN);

  /* Set frame format: 8data, 2stop bit */
  UCSRC = (1 << USBS) | (3 << UCSZ0);  
}

bool UART::IsAvailable() {
  if((UCSRA & _BV(UDRE)) == 0)
    return false;
  return true;
}

// TODO Optimise this function
uint16_t UART::Strlen(const char* str) {
  uint16_t len;
  for(len = 0; str[len]; len++);
  return len;
}

void UART::Print(const char* data) {
  for(int i = 0; i < UART::Strlen(data); i++) {
    while(!UART::IsAvailable())
      ;
    UDR = data[i];
  }
}

void UART::PutChar(unsigned char data) {
  while(!UART::IsAvailable())
    ;
  UDR = (int)data;
}

uint8_t UART::GetChar() {
  //loop_until_bit_is_set(UCSR0A, RXC0);
  while(!(UCSRA & (1 << RXC)))
    ;
  return UDR;
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
