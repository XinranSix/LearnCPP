#include "module.h"
#include <stdio.h>

void func1() { printf("fun1...\n"); }

void func2() { printf("fun2...\n"); }

int main() {

    runcallback(func1);
    runcallback(func2);

    return 0;
}
