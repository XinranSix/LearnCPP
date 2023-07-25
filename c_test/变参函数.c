#include <stdio.h>
#include <stdarg.h>

// void print_num(char *fmt, ...) {

//     va_list args;
//     va_start(args, fmt);
//     vprintf(fmt, args);
//     va_end(args);
// }

void __attribute__((format(printf, 1, 2))) my_printf(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

int main() {

    int num = 0;
    my_printf("%d %d", 1, 2);

    return 0;
}