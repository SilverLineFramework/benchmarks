#include <stdio.h>
#include <inttypes.h>
uint64_t volatile cnt = 0;

int main() {
  int n = 300;
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
      sum2 += fn(j);
    }
    if (!(i % 5000)) {
      printf("Checkpoint!\n");
    }
  }
  printf("%d\n", sum + sum2);
  printf("Instruction Count: %llu\n", cnt); 
  fn(c);

  return sum + sum2;
}


int fn(int j) {
  int sum = 0;
  for (int i = 0; i < j; i++) {
    sum += i;
  }
  return sum;
}
