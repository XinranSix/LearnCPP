#include <iostream>

template<typename T, int N>
struct ArrayInClass {
public:
    T array[N];
};

struct DoubleArrayInClass {
    double array[10];
};

template<typename T>
struct Doze {
    ArrayInClass<T, 12> contents;
};

int main(int arvc, char *argv[]) {

    ArrayInClass<double, 10> ad;
    ad.array[0] = 1.0;

    return 0;
}
