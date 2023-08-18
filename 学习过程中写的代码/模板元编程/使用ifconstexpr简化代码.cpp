#include <iostream>

template<bool Check>
auto fun() {
    if constexpr (Check) {
        return (int)0;
    } else {
        return (double)1;
    }
}

int main(int arvc, char *argv[]) {

    std::cout << fun<true>() << std::endl;
    std::cout << fun<false>() << std::endl;

    return 0;
}
