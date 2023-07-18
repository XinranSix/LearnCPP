#include <stdio.h>

char toUpper(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch + ('A' - 'a');
    }
    return ch;
}

char toLower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

int main() {

    char str[] = "     eVERY      DAY     that    you    do   not    dance,   "
                 "you   waste    one    more  day     of      your      life.";

    int len = 0;
    while (str[len] && ++len) {
    }

    int idx = 0;

    while (str[idx] == ' ') {
        str[idx] = '\0';
        idx++;
    }

    while (idx < len) {
        if (str[idx] == ' ') {
            int i = idx + 1;
            while (str[i] == ' ' && i < len) {
                str[i] = '\0';
                i++;
            }
            idx = i;
        } else {
            str[idx] = toLower(str[idx]);
            idx++;
        }
    }

    for (int i = len - 1; i >= 0; --i) {
        if (str[i] == '\0') {
            for (int j = i; j < len - 1; ++j) {
                str[j] = str[j] ^ str[j + 1];
                str[j + 1] = str[j] ^ str[j + 1];
                str[j] = str[j] ^ str[j + 1];
            }
        }
    }

    str[0] = toUpper(str[0]);

    printf("%s\n", str);

    return 0;
}
