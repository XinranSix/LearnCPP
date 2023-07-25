#include <stdio.h>

// 大小端转换的宏
#define swap_endian_u16(A) ((A & 0xFF00 >> 8) | (A & 0x00FF << 8))

int main() {

    int a = 0x11223344;

    char b;
    b = a;

    if (b == 0x44) {
        printf("小端\n");
    } else {
        printf("大端\n");
    }

    union u {
        int a;
        char b;
    } c;

    c.a = 0x11223344;
    if (c.b == 0x44) {
        printf("小端\n");
    } else {
        printf("大端\n");
    }

    return 0;
}
