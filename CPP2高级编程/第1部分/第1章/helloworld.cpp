#include <iostream>

int main(int arvc, char *argv[]) {

    int num = 0x01020304;

    short *p = reinterpret_cast<short *>(&num);
    char *q = reinterpret_cast<char *>(&num);

    printf("%#x\n", *(p + 1));

    return 0;
}
