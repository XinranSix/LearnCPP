#include "fmt/core.h"
#include <iostream>
#include <future>

int find_the_anser_to_ltuae() {
    return 1;
}

void do_other_stuff() {}

int main(int argc, char *argv[]) {

    std::future<int> the_answer = std::async(find_the_anser_to_ltuae);
    do_other_stuff();
    fmt::print("The answer is {}.\n", the_answer.get());

    return 0;
}
