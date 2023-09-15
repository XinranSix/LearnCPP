#include "fmt/core.h"
#include <iostream>
#include <string>
#include <thread>

void hello(std::string name) { fmt::print("Welcome to {}\n", name); }

int main(int argc, char *argv[]) {

    std::thread t { hello, "https://paul.pub" };
    t.join();

    return 0;
}
