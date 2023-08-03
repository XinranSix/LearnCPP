#include <iostream>
#include <cstdlib>
#include <cstring>
#include <functional>

int main() {

    std::function<int(const char *)> f = std::atoi;
    std::cout << f("1609") << std::endl;
    f = std::strlen;
    std::cout << f("1609") << std::endl;

    return 0;
}