#include <iostream>

int main(int arvc, char *argv[]) {

    int i = 3;
    int j = i;

    bool b{!true};
    bool b2{!b};

    int i1{3 + 2};
    int j1{i1 + 5};
    int k{i + j};

    int i2{5 - 1};
    int j2{5 * 2};
    int k1{j / i};

    int rem{5 % 2};

    i++;
    ++i;

    i--;
    --i;

    i += j;
    i -= j;
    i *= j;
    i /= j;
    i %= j;

    i = j & k;
    i &= k;

    i = j | k;
    i |= k;

    i = i << 1;
    i = i >> 4;
    i <<= 1;
    i >>= 4;

    i = i ^ j;
    i ^= j;

    int someInteger{256};
    short someShort;
    long someLong;
    float someFloat;
    double someDouble;

    someInteger++;
    someInteger *= 2;
    someShort = static_cast<short>(someInteger);
    someLong = someShort * 10000;
    someFloat = someLong * 0.785f;
    someDouble = static_cast<double>(someFloat);

    std::cout << someDouble << std::endl;

    int x{34 + 8 * 2 + 21 / 7 % 2};
    int y{34 + (8 * 2) + ((21 / 7) % 2)};

    return 0;
}
