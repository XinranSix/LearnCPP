#include <stdio.h>

void f() {
    int *p;
    p = __builtin_return_address(0);
    printf("f return address: %p\n", p);
    p = __builtin_return_address(1);
    printf("func return address: %p\n", p);
    p = __builtin_return_address(2);
    printf("main return address: %p\n", p);
    printf("\n");
}

void func() {
    int *p;
    p = __builtin_return_address(0);
    printf("func return address: %p\n", p);
    p = __builtin_return_address(1);
    printf("main return address: %p\n", p);
    printf("\n");
    f();
}

int main(int arvc, char *argv[]) {

    int *p;
    p = __builtin_return_address(0);
    printf("main return address: %p\n", p);
    printf("\n");
    func();
    printf("goodbye!\n");

    return 0;
}
