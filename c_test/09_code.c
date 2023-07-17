#include <stdio.h>

int test01(int n) {
    return (n > 0) && (n & (n - 1)) == 0 && (n & 0xaaaaaaaa) == 0;
}

int main() {
    int n;
    scanf("%d", &n);
    return 0;
}
