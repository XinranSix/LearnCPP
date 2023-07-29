#include <iostream>
#include <algorithm>

struct TestBind {
    void t(int n) {
        while (n--) {
            std::cout << "t\n";
        }
    }

    void t() { std::cout << "重载的t\n"; };
};

int main(int arvc, char *argv[]) {
    TestBind t_b;
    auto n =
        std::bind(static_cast<void (TestBind::*)(int)>(&TestBind::t), &t_b, 3);
    return 0;
}
