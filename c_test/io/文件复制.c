#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <src> <dest>", argv[0]);
        exit(1);
    }

    FILE *src = NULL;
    FILE *dest = NULL;

    src = fopen(argv[1], "r");
    if (src == NULL) {
        perror("fopen()");
        exit(1);
    }

    dest = fopen(argv[2], "w");
    if (dest == NULL) {
        perror("open()");
        if (src != NULL) {
            fclose(src);
            src = NULL;
        }
        exit(1);
    }

    int ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    if (dest != NULL) {
        fclose(dest);
        dest = NULL;
    }
    if (src != NULL) {
        fclose(src);
        src = NULL;
    }

    return 0;
}
