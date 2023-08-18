#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *fp = NULL;

    char *buff = NULL;
    long size = 0;

    fp = fopen("./27_code.c", "r");
    if (fp == NULL) {
        perror("fopen()");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buff = (char *)malloc(size + 1);
    if (buff == NULL) {
        perror("malloc()");
        fclose(fp);
        exit(1);
    }

    fread(buff, size, 1, fp);
    buff[size] = '\0';
    fputs(buff, stdout);

    fclose(fp);
    if (buff != NULL) {
        free(buff);
        buff = NULL;
    }

    return 0;
}
