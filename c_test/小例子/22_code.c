#include <stdio.h>

void reverseString(char *str) {
    int i = 0, j = 0;
    while (str[++j])
        ;
    if (j == 1) {
        return;
    }
    j--;
    while (i < j) {
        str[i] = str[i] ^ str[j];
        str[j] = str[i] ^ str[j];
        str[i] = str[i] ^ str[j];
        i++;
        j--;
    }
}

int main(int argc, char **argv) {

    char str[] = "abcdefg";

    printf("%s\n", str);
    reverseString(str);
    printf("%s\n", str);

    return 0;
}
