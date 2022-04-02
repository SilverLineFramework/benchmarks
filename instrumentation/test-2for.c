#include <stdio.h>
#include <inttypes.h>
uint64_t volatile cnt = 0;

int main() {
  int n = 30000;
  int a = 1;
  int b = 2;
  int c = 3;
  int k = 0;
  int l = 0;

  int sum = 0;
  int sum2 = 0;

  for (int i = 0; i < n ; i++) {
    sum += i;
    l = n * c;
    for (int j = 0; j < n; j++) {
      k = b + c;
      sum2 += k;
    }
    if (!(i % 5000)) {
      printf("Checkpoint!\n");
    }
  }
  printf("%d\n", sum + sum2);
  printf("Instruction Count: %llu\n", cnt); 

  return sum + sum2;
}
