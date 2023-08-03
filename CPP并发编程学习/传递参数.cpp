#include <iostream>
#include <string>
#include <thread>

void f(int i, std::string const &s) {
    std::cout << i << std::endl;
    std::cout << s << std::endl;
}

void oops(int some_param) {
    char buffer[1024];
    sprintf(buffer, "%i", some_param);
    std::thread t(f, 3, std::string(buffer));
    t.detach();
}

int main(int arvc, char *argv[]) {

    std::thread t(f, 3, "hello");
    t.join();

    oops(1);

    return 0;
}
