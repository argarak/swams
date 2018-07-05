
#include <stdio.h>
#include <inttypes.h>

int read() {
  return 1;
}

uint16_t getData() {
  uint16_t data = 0x00;

  for(uint8_t i = 0; i < 16; ++i) {
    if(read() == 1) {
      printf("data: 0x%04x\n", (data | (1 << i)));
      data = (data | (1 << i));
    } else {
    }
  }

  return data;
}

int main(void) {
  printf("temp: 0x%04x\n", getData());
  return 1;
}
