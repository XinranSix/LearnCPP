#include <iostream>

template <typename T>
struct Mixin1 : T {};

template <typename... Args>
struct Mixin2 : Args... {};

int main(int argc, char *argv[]) {
    std::cout << "Hello World" << std::endl;
    return 0;
}
