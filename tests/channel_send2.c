#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "api.h"

int main() {
  char path[] = "house1/hall21/light1";
  int fd = ch_open(path, CH_WRONLY, 0);
  int counter = 0;
  char* val = (char*) malloc(20);
  while(1) {
    sprintf(val, "Bounter: %d", counter);
    printf("Sending: \'%s\'\n", val);
    ch_write_msg(fd, val, strlen(val));
    sleep(1);
    counter++;
  }
  free(val);
  return 0;
}


