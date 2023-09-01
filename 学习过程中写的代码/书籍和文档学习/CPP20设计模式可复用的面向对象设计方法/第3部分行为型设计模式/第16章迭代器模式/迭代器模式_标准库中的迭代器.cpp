#include "fmt/core.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {

    std::vector<std::string> names { "john", "jane", "jill", "jack" };

    auto it { begin(names) };
    fmt::print("{}\n", *it);

    return 0;
}
