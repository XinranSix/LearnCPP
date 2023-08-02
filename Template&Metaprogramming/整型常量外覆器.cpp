#include <iostream>

struct five { // 数值 5 的整型常量外覆器
    static int const value = 5;
    using value_type = int;
};

int main(int arvc, char *argv[]) { return 0; }
