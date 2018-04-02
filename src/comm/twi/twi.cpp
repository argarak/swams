
/* There's going to be a lot of comments because I'm just learning about the
   TWI interface so I'll be referencing application note AN2480, titled
   "Using the TWI Module as I2C Master" which is available at
   http://www.microchip.com//wwwAppNotes/AppNotes.aspx?appnote=en591794 */

/* Thanks to the page on the Embedds blog:
   http://embedds.com/programming-avr-i2c-interface/
   for help in writing these functions! */

/* This page was also helpful in documenting the AVR registers for TWI:
   http://www.avrbeginners.net/architecture/twi/twi.html */

/* TWCR is the TWI Control Register (sets TWI parameters),
   TWSR is the TWI Status Register (sets mode of operation, e.g. Master),
   TWBR is the TWI Bitrate Register (corresponds to frequency, e.g. 400kHz),
   TWDR is the TWI Data Register (sends data to device),
   TWAR is the TWI Address Register (selects device address). */


#include <avr/io.h>
#include <util/twi.h> 

#include "twi.h"

#define TWI_NOT_COMPLETE ((TWCR & (1 << TWINT)) == 0)

void TWI::Init() {
  /* Setting TWI registers to clock frequency of 400kHz. According to the
     datasheet of the MCP7940M RTC I'm using, it should be OK.

     We are setting the AVR TWI registers to generate a frequency of the I2C
     protocol based on our CPU frequency. App. note AN2480 Table 1-1 shows
     common SCL frequencies and what values to set for each register.

     Since my Attiny2313 is running at 16MHz, TWBR must be 12 (hex: 0x0C) and
     TWSR must be 0 (hex: 0x00). */
  TWSR = 0x00;
  TWBR = 0x0C;

  /* Enable TWI. In TWI_Master.c (source code in app. note AN2480) there seems
     to be a different value for this register, turning off interrupts. But
     I'm guessing it's not necessary at this point. */
  TWCR = (1 << TWEN);
}

void TWI::Start() {
  /* Set the following registers:
     TWINT: Interrupt flag, has to be cleared after a TWI operation (set to 1);
     TWSTA: TWI Start flag;
     TWEN:  TWI Enable flag.

     This is combination sends a start signal to the device. */
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

  /* Wait until TWI is complete */
	while(TWI_NOT_COMPLETE);
}

void TWI::Stop() {
  /* Same as the start, however now we are setting the TWSTO (TWI Stop) register
     high alongside TWINT and TWEN. We don't have to wait for TWI to be
     complete. */
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI::Write(uint8_t data) {
  /* Provide data to TWDR. */
  TWDR = data;

  /* Enable TWI and clear interrupt so that data can be sent. */
  TWCR = (1 << TWINT) | (1 << TWEN);

  /* Wait until TWI is complete. */
  while(TWI_NOT_COMPLETE);
}

/* This read sends out an ACK signal as needed by the MCP7940M RTC, this
   acknowledges the signal read and confirms that the byte was successfully
   transmitted. */
uint8_t TWI::Read() {
  /* Clear interrupt, begin TWI and enable acknowledge signal
     (TWEA bit set to 1). */
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

  /* Wait until transfer is complete. */
  while(TWI_NOT_COMPLETE);

  /* Return the data read from the register. */
  return TWDR;
}

uint8_t TWI::Status() {
  /* Return TWSR register value.
     Possible return values are documented in
     https://www.nongnu.org/avr-libc/user-manual/group__util__twi.html
     though I cannot confirm this. */
	return TWSR;
}
