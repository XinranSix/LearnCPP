#include <assert.h>
#include <stdio.h>

int main() {

  int ia = -10;

  unsigned int ib = 4;

  if ((ia + ib) > 0) {
    printf("ia + ib > 0\n");
  } else {
    printf("ia + ib < 0\n");
  }

  printf("ia + ib = %u\n", ia + ib);
  printf("ia + ib = %d\n", ia + ib);

  assert(0);

  return 0;
}
