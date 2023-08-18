#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 拷贝
void copy(char *src, char *dest) {
    while ((*dest++ = *src++))
        ;
}

// 求长度
int length(char *str) {
    int len = 0;
    while (str[len] && ++len)
        ;
    return len;
}

// 反转
void rev(char *str) {
    int len = length(str);
    int i = 0, j = len - 1;
    while (i < j) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
}

// 追加
void append(char *str1, char *str2) {
    int len1 = 0, len2 = 0;
    while (str1[len1] && ++len1)
        ;
    while (str2[len2] && ++len2)
        ;

    int idx = 0;
    while (idx < len2) {
        str1[len1++] = str2[idx++];
    }
}

// 插入
void insert(char *src, char *str, int index) {
    int len1 = 0, len2 = 0;
    while (src[len1] && ++len1)
        ;
    while (str[len2] && ++len2)
        ;
    if (index < 0) {
        index = 0;
    }
    if (index > len1) {
        index = len1;
    }
    int m = len1 - index + 1;
    int t = len1;
    while (m--) {
        src[t + len2] = src[t];
        t--;
    }
    for (int i = 0; i < len2; ++i) {
        src[i + index] = str[i];
    }
}

void remove_substr(char *str, char *substr) {
    int len1 = 0, len2 = 0;
    while (str[len1] && ++len1)
        ;
    while (substr[len2] && ++len2)
        ;

    for (int i = 0; i <= len1 - len2; ++i) {

        int flag = 1;

        for (int j = 0; j < len2; ++j) {
            if (str[i + j] != substr[j]) {
                flag = 0;
                break;
            }
        }

        // 匹配成功
        if (flag) {
            // 将主串中的子串变成 "\0\0\0\0\0\0\0\0\0..."
            for (int k = 0; k < len2; ++k) {
                str[i + k] = '\0';
            }
            // 冒泡法把 '\0' 搞到后面去
            for (int k = len1 - 1; k >= i; --k) {
                if (str[k] == '\0') {
                    for (int j = k; j < len1 - 1; ++j) {
                        str[j] = str[j] ^ str[j + 1];
                        str[j + 1] = str[j] ^ str[j + 1];
                        str[j] = str[j] ^ str[j + 1];
                    }
                }
            }
            // 不想递归，直接指针往前拨，重新开始
            i -= len2;
        }
    }
}

int main(int arvc, char *argv[]) {

    char str[100] = "aaaaabbbbbbcccccabcacbasaehehohwvhwhiehubiebiewuhewueh";
    //                  "          bccccc  cacbasaehehohwvhwhiehubiebiewuhewueh"
    //                  "aa         cccccabcacbasaehehohwvhwhiehubiebiewuhewueh"
    char substr[] = "abb";

    remove_substr(str, substr);

    printf("%s\n", str);

    return 0;
}
