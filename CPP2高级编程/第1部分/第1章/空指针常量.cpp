#include <iostream>

void func(int i) { std::cout << "fun(int)" << std::endl; }

int main(int arvc, char *argv[]) {

    int *p = nullptr;

    func(NULL);

    return 0;
}
