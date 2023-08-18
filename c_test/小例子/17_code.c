#include <stdio.h>

int main() {
    int a[10], i, j, n;
    for (i = 0; i <= 9; i++) {
        scanf("%d", &a[i]);
    }
    for (i = 0; i <= 9; i++) {
        for (j = 0; j <= 9 - 1; j++) {
            if (a[j] > a[j + 1]) {
                n = a[j];
                a[j] = a[j + 1];
                a[j + 1] = n;
            }
        }
    }
    for (i = 0; i <= 9; i++) {
        printf("%d", a[i]);
    }
}