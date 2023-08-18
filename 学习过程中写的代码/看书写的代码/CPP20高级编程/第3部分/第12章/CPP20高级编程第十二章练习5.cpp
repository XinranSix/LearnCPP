#include <iostream>
#include <string>
#include <string_view>

using namespace std;

template <typename T>
concept ToStringable = requires(T const &t) { std::to_string(t); };

auto concat(ToStringable auto t1, ToStringable auto t2) {
    return std::to_string(t1) + std::to_string(t2);
}

auto concat(std::string_view t1, std::string_view t2) {
    return std::string { t1 } + std::string { t2 };
}

auto concat(ToStringable auto t1, std::string_view t2) {
    return std::to_string(t1) + std::string { t2 };
}

auto concat(std::string_view t1, ToStringable auto t2) {
    return std::string { t1 } + std::to_string(t2);
}

int main(int argc, char *argv[]) {

    cout << concat(1, 2.2) << endl;
    cout << concat("Hello ", "World") << endl;
    cout << concat("Hello ", 1) << endl;
    cout << concat(2, " World") << endl;

    return 0;
}
