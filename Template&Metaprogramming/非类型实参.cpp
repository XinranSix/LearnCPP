#include <iostream>

template<typename T, T nootype_param>
class C;

struct X {
    int n;
    static bool b;
};

template<typename T>
void templ_func();

int main(int arvc, char *argv[]) {

    C<int, 33> *c1;

    // int a;
    // C<int *, &a> *c2;

    void f();
    void f(int);

    C<void (*)(int), f> *c3;
    C<bool &, X::b> *c4;
    C<int X::*, &X::n> *c5;

    // C<void(), &templ_func<double>()> *c6;

    return 0;
}
