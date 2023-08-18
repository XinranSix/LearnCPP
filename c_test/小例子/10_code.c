#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    scanf("%s", s);
    int len = strlen(s);
    int i = 0, j = len - 1;
    while (i < j) {
        if (s[i] != s[j]) {
            printf("不是");
            return 0;
        }
        i++;
        j--;
    }
    printf("是");
    return 0;
}
