#include <iostream>
#include <string>

template<typename T>
void foo(T &&t) {}

int main(int arvc, char *argv[]) {

    foo(42);
    foo(3.14159);
    foo(std::string());

    int i = 42;
    foo(i);

    return 0;
}
