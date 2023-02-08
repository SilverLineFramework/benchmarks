#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "api.h"

#define PL_SIZE 1024

int main() {
  char send_path[] = "test/load_gen";
  int fd = ch_open(send_path, CH_RDONLY, 0);
  char* packet = malloc(PL_SIZE);
  uint64_t pkt_ct = 0;

  while (1) {
    if (ch_poll(&fd, 1, 6000)) {
      ch_read_msg(fd, packet, PL_SIZE);
      printf("Received: Packet %llu\n", pkt_ct);
      pkt_ct++;
    }
    else {
      printf("Timeout\n");
    }
  }
}
