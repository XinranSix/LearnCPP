#include <iostream>

template <typename T1, typename T2>
struct X {};

using OtherName = X<int, double>;

template <typename T1>
using OtherName1 = X<T1, double>;

int main(int argc, char *argv[]) {

    using MyInt = int;

    return 0;
}
