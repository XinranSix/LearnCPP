#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct buffer {
    int len;
    int a[0];
};

int main(int arvc, char *argv[]) {

    struct buffer *buf;
    buf = (struct buffer *)malloc(sizeof(struct buffer) + 20);
    buf->len = 20;
    strcpy(buf->a, "hello zhaixue.cc!\n");
    puts(buf->a);

    return 0;
}
