#include <stdio.h>
#include <inttypes.h>

uint64_t volatile cnt = 0;

int main() {
  int n = 10000;
  int a = 3;
  int b = 4;
  int k = 1;
  int j;
  int w = 0;

  //int j = 3 * k;
  if (b + 3 < 5) {
    printf("Hello");
  }

  //while (j < n) {
  for (j = 3*k; j < n; j++) {
      k = a + b;
      int l = k * 3;
      w += l;
      j++;
  }

  printf("%d\n", w + j);
  printf("Instruction Count: %lu\n", cnt);
}
