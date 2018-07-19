
#ifndef _H_COMMAND
#define _H_COMMAND

#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h>
#include <stdio.h>

#include "../comm/uart/uart.h"

namespace Command {
  int Listen();
  uint8_t GetID(char* msg);
  uint8_t Lookup(uint8_t id, char* msg);
  void OK();

  void UpdateRTC(char* msg);       /* ID: 0 */
  void UpdateStartTime(char* msg); /* ID: 1 */
  void UpdateStopTime(char* msg);  /* ID: 2 */
  void UpdateTemps(char* msg);     /* ID: 3 */
}

#endif
