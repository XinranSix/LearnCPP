#include <stdio.h>
#include <stdlib.h>

int main() {
    signed int a = -1;
    int b = 0xffffffff;
    printf("a = %d\n", a);
    printf("a = %u\n", a);

    printf("b = %d\n", b);
    printf("b = %u\n", b);

    return 0;
}
