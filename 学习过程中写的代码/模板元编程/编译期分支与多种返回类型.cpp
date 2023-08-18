#include <iostream>
#include <type_traits>

auto wrap1(bool Check) -> decltype(std::common_type_t<int, double>{}) {
    if (Check) {
        return (int)0;
    } else {
        return (double)1;
    }
}

template<bool Check, std::enable_if_t<Check> * = nullptr>
auto fun() {
    return (int)0;
}

template<bool Check, std::enable_if_t<!Check> * = nullptr>
auto fun() {
    return (double)1;
}

template<bool Check>
auto wrap2() {
    return fun<Check>();
}

int main(int arvc, char *argv[]) {

    std::cout << wrap1(true) << std::endl;
    std::cout << wrap1(false) << std::endl;
    
    std::cerr << wrap2<true>() << std::endl;
    std::cerr << wrap2<false>() << std::endl;

    return 0;
}
