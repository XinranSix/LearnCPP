#include <algorithm>
#include <format>
#include <iostream>
#include <string>

bool is_not_space(char ch) {
    return ch != ' ';
}

std::string trim_left(std::string s) {

    s.erase(begin(s), std::find_if(begin(s), end(s), is_not_space));

    return s;
}

std::string trim_right(std::string s) {
    s.erase(std::find_if(rbegin(s), rend(s), is_not_space).base(), end(s));
    return s;
}

std::string trim(std::string s) {
    return trim_left(trim_right(std::move(s)));
}

int main(int argc, char *argv[]) {

    std::cout << std::format("'{}'", trim("    hyt   ")) << std::endl;

    return 0;
}
