#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int arvc, char *argv[]) {

    char str[128];
    fgets(str, 128, stdin);
    // scanf("%s", str);

    int len = 0;

    while (str[++len])
        ;

    printf("the length of `%s` is %d\n", str, len);

    return 0;
}
