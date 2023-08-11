#include <iostream>

struct Base {
    virtual ~Base() = default;
    virtual void go(int i = 2) {
        std::cout << "Base' go with i = " << i << std::endl;
    }
};

struct Derived : Base {
    void go(int i = 7) {
        std::cout << "Derived' go with i = " << i << std::endl;
    }
};

int main(int argc, char *argv[]) {

    Base myBase;
    Derived myDerived;
    Base &myBaseReferenceToDerived { myDerived };

    myBase.go();
    myDerived.go();
    myBaseReferenceToDerived.go();

    return 0;
}
