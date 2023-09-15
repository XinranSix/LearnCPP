#include "fmt/core.h"
#include <iostream>
#include <thread>

int main(int argc, char *argv[]) {

    std::thread t { [] { fmt::print("Hello World from lambda thread.\n"); } };

    t.join();

    return 0;
}
