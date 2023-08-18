#include <iostream>

int x;

struct B {
    int i;
};

struct D : public B {};

void f(D *pd) {
    pd->i = 3;
    // D::x = 2;
}

extern int count;
int look_up_example(int count) {
    if (count < 0) {
        int count = 1;
        look_up_example(count);
    }
    return count + ::count;
}

template<typename T>
inline T const &max(T const &a, T const &b) {
    return a < b ? b : a;
}

namespace BigMath {
    class BigBumber {};
    bool operator<(BigBumber const &, BigBumber const &);
} // namespace BigMath

int main(int arvc, char *argv[]) { return 0; }
