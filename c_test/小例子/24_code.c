#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *strrchar(char *str, char ch) {
    if (str == NULL) {
        fprintf(stderr, "Given pointer is null");
        exit(1);
    }
    int len = strlen(str);
    if (ch == '\0') {
        return str + len;
    }
    if (len == 0) {
        return NULL;
    }

    while (len--) {
        if (str[len] == ch) {
            return str + len;
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    char str[100] = "";
    char ch = '1';
    char *res = strrchar(str, ch);
    if (res == NULL) {
        printf("NULL\n");
    } else {
        if (ch == '\0') {
            if (*res == '\0') {
                printf("\\0");
            } else {
                printf("%c\n", *res);
            }
        } else {
            if (*res == '\0') {
                printf("\\0");
            } else {
                printf("%c\n", *res);
            }
        }
    }

    return 0;
}
