#include <iostream>
#include <string>

template <typename T>
concept ToStringable = requires(T const &t) { std::to_string(t); };

auto concat(ToStringable auto t1, ToStringable auto t2) {
    return std::to_string(t1) + std::to_string(t2);
}

int main(int argc, char *argv[]) {

    std::cout << concat(1, 2.2) << std::endl;

    return 0;
}
