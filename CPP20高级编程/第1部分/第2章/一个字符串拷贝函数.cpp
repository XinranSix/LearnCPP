#include <iostream>
#include <cstring>
#include <string.h>

char *copyString(char const *str) {
    char *result{new char[strlen(str) + 1]};
    strcpy(result, str);
    return result;
}

char *appendStrings(char const *str1, char const *str2, char const *str3) {
    char *result{new char[strlen(str1) + strlen(str2) + strlen(str3)]};
    strcpy(result, str1);
    strcat(result, str2);
    strcat(result, str3);
    return result;
}

int main(int arvc, char *argv[]) {

    char text1[]{"abcdef"};
    size_t s1{sizeof(text1)};
    size_t s2{strlen(text1)};

    std::cout << s1 << ' ' << s2 << std::endl;

    char const *text2{"abcdef"};
    size_t s3{sizeof(text2)};
    size_t s4{strlen(text2)};

    std::cout << s3 << ' ' << s4 << std::endl;

    return 0;
}
