struct A {
    int i;

    void f() {}
};

struct B : A {};

struct C : A {};

struct D : B, C {};

int main(int argc, char *argv[]) {

    D d {};

    // d.i = 1;
    // d.f();

    return 0;
}
