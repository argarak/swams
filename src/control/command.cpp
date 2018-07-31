
#include "command.h"

char* strcpy(char *strDest, const char *strSrc) {
  char *temp = strDest;
  while(*strDest++ = *strSrc++);
  return temp;
}

uint8_t convertToInt(char* msg) {
  return (uint8_t)strtol(msg, (char **)NULL, 10);
}

/* We are only finding the length of uint8_t with a limit of 255 after all...*/
/* The actual length is decremented because of how it is used in the loop. */
uint8_t getIntLength(uint8_t n) {
  if(n >= 100) return 2;
  else if(n >= 10) return 1;
  else return 0;
}

void Command::OK() {
  UART::Print("ok\n");
}

void Command::UpdateRTC(char* msg) {
  uint8_t seconds, minutes, hours, weekday, day, month, year;

  for(uint16_t i = 0; i < UART::Strlen(msg); i++) {
    switch(msg[i]) {
    case 'S':
      seconds = convertToInt(&msg[i+1]);
      i += getIntLength(seconds);

    case 'M':
      minutes = convertToInt(&msg[i+1]);
      i += getIntLength(minutes);

    case 'H':
      hours = convertToInt(&msg[i+1]);
      i += getIntLength(hours);

    case 'W':
      weekday = convertToInt(&msg[i+1]);
      i += getIntLength(weekday);

    case 'D':
      day = convertToInt(&msg[i+1]);
      i += getIntLength(day);

    case 'N':
      month = convertToInt(&msg[i+1]);
      i += getIntLength(month);

    case 'Y':
      year = convertToInt(&msg[i+1]);
      i += getIntLength(year);
    }
  }

  Command::OK();
}

void Command::UpdateStartTime(char* msg) {
  
}

void Command::UpdateStopTime(char* msg) {
  
}

void Command::UpdateTemps(char* msg) {
  
}

uint8_t Command::GetID(char* msg) {
  return convertToInt(&msg[1]);
}

uint8_t Command::Lookup(uint8_t id, char* msg) {
  /* ID List:
     0: Update RTC
        S: Seconds
        M: Minutes
        H: Hours
        W: Week day
        D: Day
        N: Month
        Y: Year

     1: Update Light Start Time
        S: Seconds
        M: Minutes
        H: Hours
        O: On/Off

     2: Update Light Stop Time
        S: Seconds
        M: Minutes
        H: Hours
        O: On/Off

     3: Update Temps
        X: Max
        N: Min
        R: Regulated
        T: Threshold */

  switch(id) {
  case 0:
    Command::UpdateRTC(msg);
    return 0;

  case 1:
    Command::UpdateStartTime(msg);
    return 0;

  case 2:
    Command::UpdateStopTime(msg);
    return 0;

  case 3:
    Command::UpdateTemps(msg);
    return 0;

  default:
    UART::Print("err: invalid command\n");
    return 1;
  }
}

int Command::Listen() {
  char* tmsg = UART::ReadString(500);

  char msg[256];

  strcpy(msg, tmsg);
  free(tmsg);

  if(msg[0] != 'U') return 1;

  Command::Lookup(Command::GetID(msg), msg);

  return 0;
}
