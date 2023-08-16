#include <stdio.h>

union X {
    char a;
    short b;
    int c;
};

int main(int argc, char *argv[]) {

    union X x;

    x.c = 0x12345678;
    /*
    高地址 低地址
    12 34 56 78
    */
    printf("%#x\n", x.a);
    printf("%#x\n", x.b);
    printf("%#x\n", x.c);
    printf("\n");

    x.b = 0x2345;
    /*
    高地址 低地址
    12 34 23 45
    */
    printf("%#x\n", x.a);
    printf("%#x\n", x.b);
    printf("%#x\n", x.c);
    printf("\n");

    x.a = 0x62;
    /*
    高地址 低地址
    12 34 23 62
    */
    printf("%#x\n", x.a);
    printf("%#x\n", x.b);
    printf("%#x\n", x.c);
    printf("\n");

    return 0;
}
