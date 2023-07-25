#include <stdio.h>

int main() {

    // char a = 125;
    // char b = 30;
    // char c = a + b;
    // if (c < 0) {
    //     printf("溢出辣！\n");
    // } else {
    //     printf("%d\n", c);
    // }

    unsigned char a = 255;
    unsigned char b = 40;
    unsigned char c;
    c = a + b;
    if (c < a || c < b) {
        printf("溢出辣！\n");
    } else {
        printf("c = %u\n", c);
    }

    return 0;
}
