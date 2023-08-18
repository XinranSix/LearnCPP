#include <stdint.h>
#include <stdio.h>

#define T int

void listArr(void *arr, int len, int step, void (*fp)(void *)) {
    for (int i = 0; i < len; i += step) {
        fp((T *)arr + i);
    }
}

void printInt(void *elem) {
    int *p = (int *)elem;
    printf("%d\n", *p);
}

void printDoule(void *elem) {
    double *p = (double *)elem;
    printf("%lf\n", *p);
}

int main(int argc, char *argv[]) {

    int a[] = {1, 2, 3, 4, 5};
    listArr(a, 5, 1, printInt);

    return 0;
}
