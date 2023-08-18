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

        int j = 0;
        int cnt = 0;
        while (cnt < len2) {
            if (str[i + j] == '*') {
            } else if (str[i + j] != keyword[cnt]) {
                break;
            } else if (str[i + j] != '*') {
                cnt++;
            }
            j++;
        }
        if (cnt == len2) {
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

    // clang-format off
    // char str[] = "qwqweabcaabcaababcdcdbcddbcddqweqweqweqweabcaabcaababcdcdbcddbcddeqqweabcaabcaababcdcdbcddbcddwegweggwewegegwegerherthabcaabcaababcdcdbcddbcddjrtfabcaabcaababcdcdbcddbcddgfgn";
    // char keyword[] = "abcd";
    // clang-format on

    char str[] = "sssssssaabcbababccabccabc";
    char keyword[] = "abc";

    maskedKeywords(str, keyword);
    puts(str);

    return 0;
}
