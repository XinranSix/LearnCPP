#include <iostream>

template<typename T1, typename T2>
void combine(T1, T2);

class Mixer {
    friend void combine<>(int &, int &);
    friend void combine<int, int>(int, int);
    friend void combine<char>(char, int);
    // friend void combine<char>(char &, int);
    friend void combine<>(long, long);
};

void multiply(void *); // 普通函数

template<typename T>
void multiply(T); // 函数模板

class Comrades {

    // 定义了一个新的函数 ::multiply(int)
    // 非受限函数名称，不能引用模板实例
    friend void multiply(int) {}
    // 引用上面的普通函数，
    // 不会引用multiply<void*>实例
    friend void ::multiply(void *);
    // 引用一个模板实例
    friend void ::multiply(int);
    // 受限名称还可以具有一对尖括号
    // 但模板在此必须是可见的
    friend void ::multiply<double *>(double *);
    // 错误：受限的友元不能是一个定义
    // friend void ::error() {}
};

int main(int arvc, char *argv[]) { return 0; }
