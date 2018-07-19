
#include "command.h"

char* strcpy(char *strDest, const char *strSrc) {
  char *temp = strDest;
  while(*strDest++ = *strSrc++);
  return temp;
}

uint8_t Command::GetID(char* msg) {
  return (uint8_t)strtol(&msg[1], (char **)NULL, 10);
}

int Command::Listen() {
  char* tmsg = UART::ReadString();

  char msg[256];

  strcpy(msg, tmsg);
  free(tmsg);

  if(msg[0] != 'U') return 1;

  char coolbuf[64];

  sprintf(coolbuf, "ID: %i\n", Command::GetID(msg));

  UART::Print(coolbuf);

  return 0;
}
