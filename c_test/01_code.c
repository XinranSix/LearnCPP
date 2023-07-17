#include <stdio.h>

void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int main() {

    int a, b;

    while (scanf("%d %d", &a, &b) == 2) {
        printf("Before exchange: a = %d, b = %d\n", a, b);
        swap(&a, &b);
        printf("After exchange: a = %d, b = %d\n", a, b);
    }

    return 0;
}