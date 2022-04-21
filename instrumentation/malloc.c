#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint64_t volatile cnt = 0;

int main() {
  int n = 10;
  int a = 3;
  int b = 4;
  int k = 1;
  int j;
  int size = 2;
  if (b == 4) {
    size = 5;
  }
  int* w = (int*) malloc(size * sizeof(int));

  //int j = 3 * k;
  if (b + 3 < 5) {
    printf("Hello");
  }

  //while (j < n) {
  for (j = 3*k; j < n; j++) {
      k = a + b;
      int l = k * 3;
      w += l;
      char* m = (char*) malloc(20 * sizeof(char));
      for (int p = 0; p < 20; p++) {
        m[p] = p + 'A';
      }
      printf("%s\n", m);
      j++;
  }

  printf("%d\n", w[0] + j);
  printf("Instruction Count: %lu\n", cnt);
}
