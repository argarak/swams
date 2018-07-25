
#include "adc.h"

void ATDC::Init() {
  ADMUX = (1 << REFS0); /* Set reference to internal 5V source */

  /* Set ADC to channel 2 */
  ADMUX |= (2 & 0b00000111);

  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ATDC::ReadValue() {
  ADCSRA |= (1 << ADSC);

  while(ADCSRA & (1 << ADSC));

  return (ADC);
}
