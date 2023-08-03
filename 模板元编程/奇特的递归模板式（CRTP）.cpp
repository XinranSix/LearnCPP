#include <iostream>

template<typename D>
struct Base {
    template<typename TI>
    void Fun(const TI &input) {
        D *ptr = static_cast<D *>(this);
        ptr->Imp(input);
    }

    static void Fun() { D::Imp(); }
};

struct Derived : public Base<Derived> {
    template<typename TI>
    void Imp(const TI &input) {
        std::cout << input << std::endl;
    }

    static void Imp() {
        std::cout << "Implementation from derive class." << std::endl;
    }
};

int main(int arvc, char *argv[]) {

    Derived d;
    d.Fun("Implementation from derive class.");

    Derived::Fun();

    return 0;
}
