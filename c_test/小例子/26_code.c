#include <stdlib.h>
#include <stdio.h>

int str2Int(char *str) {
    if (str == NULL) {
        fprintf(stderr, "花 Q");
        exit(1);
    }
    int res = 0;
    int idx = 0;
    int op = 1;
    while (str[idx] != '\0') {
        if (idx == 0 && str[idx] != '-' || idx != 0) {
            if (str[idx] < '0' || str[idx] > '9') {
                return res * op;
            } else {
                res = res * 10 + str[idx] - '0';
            }
        } else {
            op = -1;
        }

        idx++;
    }
    return res * op;
}

int main(int argc, char *argv[]) {

    printf("%d\n", str2Int("2134"));
    printf("%d\n", str2Int("2134a123"));
    printf("%d\n", str2Int("a123"));
    printf("%d\n", str2Int("1sa123"));
    printf("%d\n", str2Int("-2134"));
    printf("%d\n", str2Int("-2134a123"));
    printf("%d\n", str2Int("-a123"));
    printf("%d\n", str2Int("-1sa123"));
    printf("%d\n", str2Int("-"));
    return 0;
}
