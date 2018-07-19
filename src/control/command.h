
#ifndef _H_COMMAND
#define _H_COMMAND

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include "../comm/uart/uart.h"

namespace Command {
  int Listen();

  uint8_t GetID(char* msg);
  char* TrimID(char* msg);

  void Lookup(uint8_t id, char* msg);

  void SendOK();
}

#endif
