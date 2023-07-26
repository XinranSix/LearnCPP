#include <iostream>

template<size_t... args>
constexpr int v = (args - ...);

template<size_t... args>
constexpr int v2 = (... - args);

template<class... Args>
void printer(Args &&...args) {
    (std::cout << ... << args) << '\n';
}

template<class... Args>
void print(Args... args) {
    ((std::cout << args << ' '), ...);
}

int main(int argc, char **argv) {
    std::cout << v<4, 5, 6> << '\n';  // (4 - (5 - 6)) = 5
    std::cout << v2<4, 5, 6> << '\n'; // ((4 - 5) - 6) = -7
    print("**", 1.2, 1);  // 
    return 0;
}
