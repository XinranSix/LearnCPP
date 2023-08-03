#include <iostream>

struct X {
    void f() { std::cout << "6\n"; }
    template<typename Ty>

    auto operator->*(Ty v) {
        return (this->*v)();
    }
};

int main(int arvc, char *argv[]) {
    X x;
    x->*&X::f;
    return 0;
}

// operator.*不可以重载，但是operator->*可以重载
