#include <stdio.h>
#include "module.h"

void runcallback(void (*fp)(void)) { fp(); }

int send_data(char *buf, int len) {
    char data[100];
    int i;
    for (i = 0; i < len; ++i) {
        data[i] = buf[i];
    }
    for (i = 0; i < len; ++i) {
        printf("received data[%d] = %d\n", i, data[i]);
    }
    return len;
}
