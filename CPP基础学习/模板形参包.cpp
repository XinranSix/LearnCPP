#include <concepts>
#include <iostream>

template<size_t... args>
struct X {
    void f() {
        for (const auto &i : {args...}) {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    }
};

template<typename... Args>
void f(Args... args) {
    ((std::cout << args << ' '), ...);
    std::cout << std::endl;
}

template<std::integral... Args>
void f2(Args... args) {
    ((std::cout << args << ' '), ...);
    std::cout << std::endl;
}

void print() {}

template<class T, class... Args>
void print(T t, Args... args) {
    std::cout << t << ' ';
    print(args...);
}

template<size_t... Args>
void t() {
    int array[sizeof...(Args)]{Args...};
    for (const auto &i : array) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

int main() {
    X<1, 2, 3, 4, 5, 6> x;
    x.f();
    f(1, 2, 3, "*");
    f2(1, 2, 3);
    t<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>();
    return 0;
}
