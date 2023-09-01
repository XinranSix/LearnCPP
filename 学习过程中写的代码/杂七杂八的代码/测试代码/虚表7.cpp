struct A {
    int i;

    virtual void f() {}
};

struct B : virtual A {};

struct C : virtual A {};

struct D : B, C {};

int main(int argc, char *argv[]) { return 0; }
