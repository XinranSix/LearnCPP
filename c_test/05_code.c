#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) {

    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= i; ++j) {
            printf("+——————————");
        }
        printf("+\n");
        printf("|");
        for (int j = 1; j <= i; ++j) {
            printf("%d * %d = %2d|", j, i, i * j);
        }
        printf("\n");
    }
    for (int j = 1; j <= 9; ++j) {
        printf("+——————————");
    }
    printf("+\n");

    return 0;
}
