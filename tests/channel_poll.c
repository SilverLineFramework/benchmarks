#include "api.h"

int main() {
  int i = 10;
  char path[] = "house1/+/light1";
  int fd = ch_open(path, CH_RDONLY, 0);
  for (int i = 0; i < 10; i++) {
    ch_poll(&fd, 1, 2000);
  }
}
