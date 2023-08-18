#include <stdio.h>

int main(int argc, char *argv[]) {

    int num = 0x01020304;

    // short *p = (short *)&num;
    char *q = (char *)&num;

    short num1 = (num >> 8);

    // printf("%#x\n", *(p + 1));
    // printf("%#x\n", *(q + 2));

    printf("%#x\n", num1);

    return 0;
}
