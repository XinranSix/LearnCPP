#include <iostream>
#include <stdexcept>

void g() {
    throw std::invalid_argument { "Some exceprion" };
}

void f() {
    try {
        g();
    } catch (std::invalid_argument const &e) {
        std::cout << "caught in f: " << e.what() << std::endl;
        throw;
    }
}

int main(int argc, char *argv[]) {

    try {
        f();
    } catch (std::invalid_argument const &e) {
        std::cout << "Caught in main: " << e.what() << std::endl;
    }

    return 0;
}
