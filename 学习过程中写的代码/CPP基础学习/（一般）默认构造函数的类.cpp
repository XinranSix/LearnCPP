#include <iostream>

class CX {
private:
    int a;
    int b;

public:
    CX() = default;
    constexpr CX(int a_, int b_) : a(a_), b(b_) {}

    constexpr int get_a() const { return a; }
    constexpr int get_b() const { return b; }
    constexpr int foo() const { return a + b; }
};

constexpr CX create_cx() { return CX(); }

constexpr CX clone(CX val) { return val; }

constexpr CX make_cx(int a) { return CX(a, 1); }

constexpr CX half_double(CX old) {
    return CX(old.get_a() / 2, old.get_b() * 2);
}

int main(int arvc, char *argv[]) { return 0; }
