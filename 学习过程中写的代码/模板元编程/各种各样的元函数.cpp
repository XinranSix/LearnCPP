#include <iostream>

template<typename T>
struct Fun_ {
    using type = T;
};

struct Fun {
    using type = int;
};

// constexpr int fun() { return 10; }

template<int a>
constexpr int fun = a + 1;

// 多个返回值
template<>
struct Fun_<int> {
    using reference_type = int &;
    using const_reference_type = const int &;
    using value_type = int;
};

int main(int arvc, char *argv[]) {
    std::cout << fun<3> << std::endl;
    return 0;
}
