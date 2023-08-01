#include <iostream>
#include <variant>

using RT1 = char;
using RT2 = struct {
    char a[2];
};

template<typename T>
RT1 test(typename T::X const *);

template<typename T>
RT2 test(...);

template<int I>
void f(int (&)[24 / (4 - I)]);

template<int I>
void f(int (&)[24 / (4 + I)]);

#define type_has_member_type_X(T) (sizeof(test<T>(0)) == 1)

int main(int arvc, char *argv[]) {




    return 0;
}
