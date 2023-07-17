#include <stdio.h>

int main() {
    int x, y, z;
    while (scanf("%d %d %d", &x, &y, &z) == 3) {
        int a = (x < y) ? (x < z ? x : z) : (y < z ? y : z);
        int c = (x > y) ? (x > z ? x : z) : (y > z ? y : z);
        int b = x + y + z - a - c;
        printf("%d %d %d\n", a, b, c);
    }
    return 0;
}
