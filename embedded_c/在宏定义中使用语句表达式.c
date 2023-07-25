#include <stdio.h>

#define MAX(x, y)                                                              \
    ({                                                                         \
        typeof(x) _x = x;                                                      \
        typeof(y) _y = y;                                                      \
        (void)(&_x == &_y);                                                    \
        _x > _y ? _x : _y;                                                     \
    })

int main(int arvc, char *argv[]) {

    int i = 2;
    int j = 6;

    printf("max = %d\n", MAX(i++, j++));
    printf("max = %f\n", MAX(3.14, 3.15));

    return 0;
}
