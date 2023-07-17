#include <stdio.h>
#include <string.h>

int main() {

    int n = 0;
    scanf("%d", &n);
    int a[n + 1];
    memset(a, 0, sizeof(int) * (n + 1));
    a[1] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = n; j >i ; --j) {
            printf(" ");
        }
        printf("/");
        for (int j = 1; j <= i; ++j) {
            printf("%02d  ", a[j]);
        }
        printf("\b\b\\\n");
        for (int j = n; j >= 1; --j) {
            a[j] += a[j - 1];
        }
    }

    return 0;
}
