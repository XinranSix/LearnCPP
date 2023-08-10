#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    int *p = (int *)malloc(sizeof(int));
    if (p == NULL) {
        perror("malloc()");
        exit(1);
    }
    memset(p, 0, sizeof(int));
    // 一顿操作
    free(p);

    return 0;
}
