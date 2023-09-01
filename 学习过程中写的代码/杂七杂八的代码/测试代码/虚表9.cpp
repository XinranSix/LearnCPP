/*
g++ -fdump-class-hierarchy 多继承.cpp ─╯ g++ -fdump-lang-class 多继承.cpp ─╯
*/

class Class_A {
public:
    virtual void fa() {}
    void fa_nv() {}
    int ia;
};

/*
--------
----xxxx
*/

class Class_B {
public:
    virtual void fb() {}
    int ib;
};
/*
--------
----xxxx
*/

class Class_C : public Class_A, public Class_B {
public:
    virtual void fa() {}
    virtual void fb() {}
    virtual void fc() {}
    int ic;
};

/*
--------
----xxxx
--------
--------
*/

int main(int argc, char const *argv[]) {
    Class_A a;
    Class_B b;
    Class_C c;
    int temp;
    Class_A &ref_A = c;
    Class_B &ref_B = c;
    Class_C *pc = &c;

    ref_A.fa();
    temp = ref_A.ia;
    ref_B.fb();
    temp = ref_B.ib;
    pc->fc();
    temp = pc->ic;

    return 0;
}