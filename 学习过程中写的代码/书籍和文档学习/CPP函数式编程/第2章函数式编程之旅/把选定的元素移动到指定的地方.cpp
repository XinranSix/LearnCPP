#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

std::string title(std::pair<std::string, bool> const &item) {
    return item.first + std::string(item.second, '*');
}

bool is_selected(std::pair<std::string, bool> const &item) {
    return item.second;
}

bool is_not_selected(std::pair<std::string, bool> const &item) {
    return !item.second;
}

template <typename It>
void move_selected_to(It first, It last, It destination) {
    std::stable_partition(first, destination, is_not_selected);
    std::stable_partition(destination, last, is_selected);
}

int main(int argc, char *argv[]) {

    std::vector<std::pair<std::string, bool>> people { { "David", true },   { "Jane", false },
                                                       { "Martha", false }, { "Peter", false },
                                                       { "Rose", true },    { "Tom", true } };

    move_selected_to(begin(people), end(people), begin(people) + 3);

    for (const auto &person : people) {
        std::cout << title(person) << '\n';
    }

    return 0;
}
