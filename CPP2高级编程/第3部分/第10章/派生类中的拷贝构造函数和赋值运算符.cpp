#include <iostream>

struct Base {
public:
    virtual ~Base() = default;
    Base() = default;
    Base(Base const &src) {
    }
};

struct Derived : public Base {
    Derived() = default;
    Derived(Derived const &src) : Base { src } {
    }

    Derived &operator=(Derived const &rhs) {
        if (&rhs == this) {
            return *this;
        }
        Base::operator=(rhs);
        return *this;
    }
};

int main(int argc, char *argv[]) {
    return 0;
}
