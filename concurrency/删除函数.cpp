#include <iostream>

class no_copies {
public:
    no_copies() {}

    no_copies(no_copies const &) = delete;
    no_copies &operator=(no_copies const &) = delete;
};

void foo(short);
void foo(int) = delete;

int main(int arvc, char *argv[]) {
   // foo(42);        // 错误，int重载声明已经删除
    foo((short)42); // OKreturn 0;
}
