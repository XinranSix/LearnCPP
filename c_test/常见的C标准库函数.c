#include <stdio.h>

int main(int arvc, char *argv[]) {

    char a[100];
    __builtin_memcpy(a, "hello world!", 20);
    __builtin_puts(a);

    return 0;
}
