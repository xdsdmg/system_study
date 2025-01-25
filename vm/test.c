#include <stdio.h>
#include <stdlib.h>

int main() {
  int x[10];
  printf("x: %lu\n", sizeof(x));

  int *b = malloc(10 * sizeof(int));
  printf("b: %lu\n", sizeof(b));

  return 0;
}
