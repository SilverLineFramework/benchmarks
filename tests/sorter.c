#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "api.h"

static int arr[10];
static char msg[220];

int cmpfunc (const void *a, const void *b) {
  return ( *(uint32_t*)a - *(uint32_t*)b );
}


void print_sort(char *msg) {
  char *token = strtok(msg, ",");
  int i = 0;
  while (token != NULL) {
    arr[i++] = atoi(token);
    token = strtok(NULL, ",");
  }
  if (i == 10) {
    printf("Sorted: ");
  }
  qsort(arr, 10, sizeof(int), cmpfunc);
  for (i = 0; i < 10; i++) {
    printf("%u,", arr[i]);
  }
  printf("\n");
}

int main() {
  char req[] = "sorter/req";
  char in[] = "sorter/acc";

  int fd = ch_open(in, CH_RDONLY, 0);
  int gd = ch_open(req, CH_WRONLY, 0);

  srand(time(0));

  while (1) {
    // Sleep between 0.3s and 2s
    int sleep_time = 1000 * (300 + rand() % 1700);
    usleep(sleep_time);
    // Send req
    char req[2] = "r";
    ch_write_msg(gd, req, 1);
    // Wait for message
    ch_poll(&fd, 1, 4000);
    if (ch_read_msg(fd, msg, 220)) {
      // Get vals and sort
      printf("Received: %s\n", msg);
      print_sort(msg);
    }
  }
}
