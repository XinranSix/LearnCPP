struct A {
    int i;

    void f() {}
};

struct B : virtual A {};

struct C : virtual A {};

struct D : B, C {};

int main(int argc, char *argv[]) {

    // D d {};

    // d.i = 1;
    // d.f();

    return 0;
}
