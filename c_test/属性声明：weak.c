#include <stdio.h>

void __attribute__((weak)) func();
int num __attribute__((weak));

int main(int arvc, char *argv[]) {
    printf("Hello World");
    return 0;
}
