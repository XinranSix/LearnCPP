#include <iostream>
#include <type_traits>

template<int a, int b>
struct Add_ {
    constexpr static int value = a + b;
};

template<int a, int b>
constexpr int Add = a + b;

constexpr int x1 = Add_<2, 3>::value;
constexpr int x2 = Add<2, 3>;

int main(int arvc, char *argv[]) {

    std::remove_reference<int &>::type h1 = 3;
    std::remove_reference_t<int &> h2 = 3;

    return 0;
}
