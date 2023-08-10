#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void maskedKeywords(char *str, char *keyword) {
    if (str == NULL) {
        fprintf(stderr, "str 为空");
        exit(1);
    }
    if (keyword == NULL) {
        fprintf(stderr, "keyword 为空");
        exit(1);
    }
    int len1 = strlen(str);
    int len2 = strlen(keyword);

    if (len2 > len1) {
        fprintf(stderr, "花 Q");
        return;
    }
    if (len2 == 0) {
        return;
    }

    int i = 0;
    while (i < len1 - len2 + 1) {
        // int cnt = 0;
        int j = 0;
        int cnt1 = 0;
        while (cnt1 < len2) {
            if (str[i + j] == '*') {
                // ++cnt;
            } else if (str[i + j] != keyword[cnt1]) {
                break;
            } else if (str[i + j] != '*') {
                cnt1++;
            }
            j++;
        }
        if (cnt1 == len2) {
            for (int k = i; k < j + i; ++k) {
                str[k] = '*';
            }
            i = 0;
            continue;
        }
        i++;
    }
}

int main(int argc, char *argv[]) {

    char str[] = "aaaabbbbbbbbabbaabbbbcc";
    char keyword[] = "aabb";
    maskedKeywords(str, keyword);
    puts(str);

    return 0;
}
