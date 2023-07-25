#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct buffer1 {
    int len;
    int a[0];
};

struct buffer2 {
    int len;
    int *a;
};

int main(int arvc, char *argv[]) {

    printf("buffer1: %ld\n", sizeof(struct buffer1));
    printf("buffer2: %ld\n", sizeof(struct buffer2));

    return 0;
}
