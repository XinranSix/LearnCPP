#include <stdio.h>

void _f() { printf("_f\n"); }

void f() __attribute((alias("_f")));

int main(int arvc, char *argv[]) {
    f();
    return 0;
}
