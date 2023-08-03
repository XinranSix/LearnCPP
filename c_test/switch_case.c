#include <stdio.h>

int main(int argc, char *argv[]) {

    char ch1 = 'A';
    char ch2 = 'a';

#ifdef UPPER_TO_LOWER
    if (ch >= 'A' && ch <= 'Z') {
        printf("%c\n", ch1);
    }
#endif
#ifdef LOWER_TO_UPPER
    if (ch >= 'a' && ch <= 'z') {
        printf("%c\n", ch2);
    }
#endif

    return 0;
}
