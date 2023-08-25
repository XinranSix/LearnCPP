#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <format>
#include <functional>

void func(int num, std::string_view str) {
    std::cout << format("func({}, {})", num, str) << std::endl;
}

int main() {
    // Bind second argument to a fixed value.
    std::string myString { "abc" };
    auto f1 { [&myString](int num) { func(num, myString); } };
    f1(16);

    // Rearrange arguments
    auto f2 { [](std::string myString, int num) { func(num, myString); } };
    f2("Test", 32);

    return 0;
}
