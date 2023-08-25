#include <iostream>

consteval unsigned long long fibonacci(size_t n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    int a { 0 }, b { 1 }, c { 0 };
    for (int i = 1; i < n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int main(int argc, char *argv[]) {

    std::cout << fibonacci(0) << std::endl;
    std::cout << fibonacci(1) << std::endl;
    std::cout << fibonacci(2) << std::endl;
    std::cout << fibonacci(3) << std::endl;
    std::cout << fibonacci(4) << std::endl;
    std::cout << fibonacci(5) << std::endl;
    std::cout << fibonacci(6) << std::endl;
    std::cout << fibonacci(7) << std::endl;
    std::cout << fibonacci(8) << std::endl;
    std::cout << fibonacci(9) << std::endl;
    std::cout << fibonacci(10) << std::endl;
    std::cout << fibonacci(11) << std::endl;
    std::cout << fibonacci(12) << std::endl;
    std::cout << fibonacci(13) << std::endl;
    std::cout << fibonacci(14) << std::endl;

    return 0;
}
