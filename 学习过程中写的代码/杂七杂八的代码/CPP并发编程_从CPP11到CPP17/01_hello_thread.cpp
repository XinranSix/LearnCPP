#include "fmt/core.h"
#include <iostream>
#include <thread>

void hello() { fmt::print("Hello World from new thread."); }

int main(int argc, char *argv[]) {

    std::thread t { hello };

    t.join();

    return 0;
}
