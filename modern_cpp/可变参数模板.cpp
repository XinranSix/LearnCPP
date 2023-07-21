#include <iostream>

void print() { std::cout << std::endl; }

template<class T, class... Args>
void print(T v, Args... args) {
    std::cout << v << ' ';
    print(args...);
}

int main(int arvc, char *argv[]) {

    print("*", 1, 1.2);

    return 0;
}
