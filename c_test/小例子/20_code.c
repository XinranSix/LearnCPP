#include <stdio.h>

int main(int argc, char *argv[]) {

    int a = 0x10203040;

    int *p = &a;
    char *q = p;

    int res = 0;

    for (int i = 0; i < sizeof(res); ++i) {
        res += *(q + i) << (8 * i);
    }

    printf("%#x\n", res);

    return 0;
}
