
#include "pwm.h"

#define PWM_PIN B,2

void PWM::Init(uint16_t dc) {
  /* Set PWM for LED Strip */
  io_output_mode(DDR(PWM_PIN), BITD(PWM_PIN));

  ICR1 = 0xFFFF;

  OCR1B = dc;

  TCCR1A |= (1 << COM1A1)|(1 << COM1B1);

  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12)|(1 << WGM13);
    
  TCCR1B |= (1 << CS10);
}

void PWM::SetDutyCycle(uint16_t dc) {
  OCR1B = dc;  
}
