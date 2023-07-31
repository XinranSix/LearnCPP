#include <iostream>

// template<unsigned long N>
// struct binary {
//     static unsigned const value = binary<N / 10>::value * 2 + N % 10;
// };

// template<>
// struct binary<0> {
//     static unsigned const value = 0;
// };

// unsigned const one = binary<1>::value;
// unsigned const three = binary<11>::value;
// unsigned const five = binary<101>::value;

// unsigned binary(unsigned long N) {
//     return N == 0 ? 0 : N % 10 + 2 * binary(N / 10);
// }

unsigned binary(unsigned long N) {
    unsigned result = 0;
    for (unsigned bit = 0x1; N; N /= 10, bit <<= 1) {
        if (N % 10) {
            result += bit;
        }
    }
    return result;
}

int main(int arvc, char *argv[]) {

    // std::cout << binary<101010>::value << std::endl;

    return 0;
}
