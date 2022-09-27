#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "api.h"

int main() {
  char path[] = "house1/+/light1";
  int fd = ch_open(path, CH_RDONLY, 0);
  char* val = (char*) malloc(20);
  for (int i = 0; i < 10; i++) {
    ch_poll(&fd, 1, 4000);
    ch_read_msg(fd, val, 20);
    printf("Read: \'%s\'\n", val);
    strcpy(val, "DEADBEEF");
  }
  free(val);
  return 0;
}


