#include <stdio.h>

int main() {
    int i = 1;
    int j = 2;
    printf("%d\n", i++ * i++); // 1 * 2 = 2
    printf("%d\n", i++ + j); // 3 + 2 = 5
    return 0;
}
