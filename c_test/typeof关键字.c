#include <stdio.h>

int main(int arvc, char *argv[]) {

    int i = 2;
    typeof(i) k = 6;

    int *p = &k;
    typeof(p) q = &i;

    printf("k = %d\n", k);
    printf("*p = %d\n", *p);
    printf("i = %d\n", i);
    printf("*q = %d\n", *q);

    

    return 0;
}