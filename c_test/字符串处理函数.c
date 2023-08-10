#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test01() {
    int len = 0;
    char *str = (char *)malloc(20);
    if (NULL == str) {
        perror("malloc()");
        exit(1);
    }

    strcpy(str, "Hello World");

    len = strlen(str);

    printf("strlen(str) = %d\n", len);

    if (str != NULL) {
        free(str);
        str = NULL;
    }
}

void test02() {
    char *src = "Hello world";
    char dest[16] = {0};
    strncpy(dest, src, 7);
    printf("%s\n", dest);
}

void test03() {
    
}

int main(int argc, char *argv[]) {

    test01();
    test02();
    test03();

    return 0;
}
