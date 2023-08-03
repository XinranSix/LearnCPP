#include <iostream>

template<typename T>
class MyClass {
public:
    void foo(T value) {
        typename T::value_type localVar; // 对于依赖类型使用 'typename' 关键字
        // T::template innerTemplate<int> t; // 对于嵌套的依赖模板使用
        // 'template' 关键字
    }
};

int main(int arvc, char *argv[]) { return 0; }
