/*
g++ -fdump-class-hierarchy 多继承.cpp ─╯ g++ -fdump-lang-class 多继承.cpp ─╯
*/

struct A {
    int i {};
};

struct B {
    int i {};
};

struct C : virtual A, virtual B {
    int ic {};
};

int main(int argc, char const *argv[]) {

    C c {};
    // c.i;

    return 0;
}