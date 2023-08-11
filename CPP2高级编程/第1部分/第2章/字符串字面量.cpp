#include <iostream>

int main(int arvc, char *argv[]) {

    std::cout << "Hello World" << std::endl;

    // char *ptr1{"hello"};
    // ptr1[1] = 'a';

    // char const *ptr2{"hello"};
    // ptr2[1] = 'a';

    char arr[]{"hello"};
    arr[1] = 'a';

    const char *str1{"Hello \"World\"!"};
    const char *str2{R"(Hello "World"!)"};
    const char *str3{R"(Line 1 
    Line 2)"};
    const char *str4{R"-(Embedded )" characters)-"};
    std::cout << str4 << std::endl;

    return 0;
}
