#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "api.h"

int main() {
  char path[40] = "sorter/input/";

  srand(time(0));
  char uuid[20];
  sprintf(uuid, "%d", rand());
  strcat(path, uuid);

  printf("%s\n", path);
  int fd = ch_open(path, CH_WRONLY, 0);

  while(1) {
    int num = rand() % 1000;
    char msg[20];
    sprintf(msg, "%d", num);
    printf("Sending %s\n", msg);
    ch_write_msg(fd, msg, strlen(msg) + 1);
    usleep(400 * 1000);
  }
  return 0;
}
