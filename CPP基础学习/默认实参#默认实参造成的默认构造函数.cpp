#include <iostream>

class C {
    void f(int i = 3);
    void g(int i, int j = 99);
    C(int arg);
};

// void C::f(int i = 3) {}

// void C::g(int i = 88, int j) {}

// C::C(int arg = 1) {}

int main(int arvc, char *argv[]) { return 0; }








/*
对于非模板类的成员函数，类外的定义中允许出现默认实参，
并与类体内的声明所提供的默认实参组合。
如果类外的默认实参会使成员函数变成默认构造函数或复制/移动(C++11
起)构造函数/赋值运算符，
那么程序非良构。对于类模板的成员函数，所有默认实参必须在成员函数的初始声明处提供。
*/