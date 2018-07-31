
#include "buzzer.h"

#define BUZZ_PIN D,6

void Buzzer::Init() {
  io_output_mode(DDR(BUZZ_PIN), BITD(BUZZ_PIN));
}

void Buzzer::Beep(uint8_t len1, uint8_t len2, uint8_t len3) {
  io_set_high(PORT(BUZZ_PIN), BIT(BUZZ_PIN));

  for(uint16_t i = 0; i < (len1 * 100); ++i) {
    _delay_ms(1);
  }
  
  io_set_low(PORT(BUZZ_PIN), BIT(BUZZ_PIN));

  for(uint16_t i = 0; i < (len1 * 100); ++i) {
    _delay_ms(1);
  }

  io_set_high(PORT(BUZZ_PIN), BIT(BUZZ_PIN));

  for(uint16_t i = 0; i < (len2 * 100); ++i) {
    _delay_ms(1);
  }
  
  io_set_low(PORT(BUZZ_PIN), BIT(BUZZ_PIN));

  for(uint16_t i = 0; i < (len2 * 100); ++i) {
    _delay_ms(1);
  }

  io_set_high(PORT(BUZZ_PIN), BIT(BUZZ_PIN));

  for(uint16_t i = 0; i < (len3 * 100); ++i) {
    _delay_ms(1);
  }
  
  io_set_low(PORT(BUZZ_PIN), BIT(BUZZ_PIN));
}
