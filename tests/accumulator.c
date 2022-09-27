#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "api.h"

int main() {
  char in[] = "sorter/input/#";
  char re[] = "sorter/req";
  char out[] = "sorter/acc";
  int fd = ch_open(in, CH_RDONLY, 0);
  int rd = ch_open(re, CH_RDONLY, 0);
  int gd = ch_open(out, CH_WRONLY, 0);

  static int accumulator[200];
  static int ct = 0;
  char val[20];
  char req[1];
  char send[20];
  int read_stat = 0;
  while (1) {
    if (ct != 200) {
      ch_poll(&fd, 1, 4000);
      ch_read_msg(fd, val, 20);
      printf("Got msg: %s\n", val);
      int num = atoi(val);
      accumulator[ct++] = num;
      if (((ct % 10) == 0)) {
        printf("Accumulated %d\n", ct);
      }
    }
    read_stat |= ch_read_msg(rd, req, 1);
    // Send last 10 data
    if ((ct > 10) && read_stat) {
      read_stat = 0;
      printf("========= SENDING 10 ======== \n");
      char msg[220] = "\0";
      ct -= 10;
      for (int i = 0; i < 10; i++) {
        char v[20];
        sprintf(v, "%u,", accumulator[ct+i]);
        strcat(msg, v);
      }
      msg[strlen(msg)-1] = 0;
      printf("Sending %s\n", msg);
      ch_write_msg(gd, msg, strlen(msg));
    }
  }
}
