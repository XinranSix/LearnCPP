#include <iostream>

[[nodiscard]] int func(int a, [[maybe_unused]] int b) { return 42; }

[[noreturn]] void forceProgramTermination() { std::exit(1); }

[[deprecated]] void fun() {}

int main(int arvc, char *argv[]) {
    fun();
    return 0;
}
