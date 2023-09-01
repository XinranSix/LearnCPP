/*
g++ -fdump-class-hierarchy 多继承.cpp ─╯ g++ -fdump-lang-class 多继承.cpp ─╯
*/

struct A {
    int ia {};
};

struct B : A {
    int ib {};
};

struct C : B {
    int ic {};
};

int main(int argc, char const *argv[]) { return 0; }