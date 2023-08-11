#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    char *str = "mail.fya@1000phone.com";
    char res[512] = {0};

    sscanf(str, "%*5s%[^.]s", res);
    puts(res);

    return 0;
}
