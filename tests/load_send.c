#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "api.h"

#define PL_SIZE 512
#define US 1
#define INTERVAL 200 * US

int main() {
  char send_path[] = "test/load_gen";
  int fd = ch_open(send_path, CH_WRONLY, 0);
  char* packet = malloc(PL_SIZE);

  while (1) {
    ch_write_msg(fd, packet, PL_SIZE);
    usleep(INTERVAL);
  }
  return 0;
}
