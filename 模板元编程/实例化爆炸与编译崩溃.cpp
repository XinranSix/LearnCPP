#include <iostream>

template<size_t ID>
struct imp {
    constexpr static size_t value = ID + imp<ID - 1>::value;
};

template<>
struct imp<0> {
    constexpr static size_t value = 0;
};

template<size_t A>
struct Warp_ {

    template<size_t ID>
    constexpr static size_t value = imp<A + ID>::value;
};

int main(int arvc, char *argv[]) {

    std::cerr << Warp_<3>::value<2> << std::endl;
    std::cerr << Warp_<10>::value<2> << std::endl;

    return 0;
}
