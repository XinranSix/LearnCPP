#include <iostream>
#include <fmt/core.h>

int main(int arvc, char *argv[]) {

    // std::cout << "Hello World!" << std::endl;
    // std::cout << "There are " << 219 << " ways I love you." << std::endl;
    // std::cout << fmt::format("There are {} ways I love you.", 219) <<
    // std::endl;

    int a[5] = {1, 2, 3, 4, 5};
    int *p = a;
    printf("%d %d", *(++p), *(p++));

    return 0;
}
