/**
 * @file 02_code.c
 * @author Yao J (jieyao.lxr@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-07-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>

/**
 * @brief 将小写字符转换成大写字符，将大写字符转换成小写字符
 *
 * @param ch 要转换的字符的指针（地址）
 */
void toggle_case(char *ch) {
    if ('a' <= *ch && *ch <= 'z') {
        *ch = *ch + 'A' - 'a';
    } else if ('A' <= *ch && *ch <= 'Z') {
        *ch = *ch + 'a' - 'A';
    } else {
        printf("Please enter a English alphabet");
    }
}

int main() {
    printf("space to quit!");
    char ch;
    while ((ch = getchar()) != ' ') {
        printf("%c ", ch);
        toggle_case(&ch);
        printf("%c\n", ch);
    }
    return 0;
}
