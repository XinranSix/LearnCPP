#include <stdio.h>

int main() {

    int a = (int)3.14;
    printf("a = %d\n", a);
    float b = (float)3;
    printf("b = %f\n", b);
    printf("\n");

    char c1 = 1;
    char c2 = -2;
    int d;
    d = (int)c1;
    printf("d = %d\n", d);
    printf("d = %x\n", d);
    d = (int)c2;
    printf("d = %d\n", d);
    printf("d = %x\n", d);
    printf("\n");

    d = 0x11223344;
    c1 = (char)d;
    printf("%x\n", c1);
    printf("%u\n", c1);
    printf("\n");

    int i = -1;
    unsigned int j = i;
    printf("-1 = %x\n", -1);
    printf("i = %d\n", i);
    printf("i = %x\n", i);
    printf("j = %u\n", j);
    printf("j = %x\n", j);
    printf("\n");

    return 0;
}
