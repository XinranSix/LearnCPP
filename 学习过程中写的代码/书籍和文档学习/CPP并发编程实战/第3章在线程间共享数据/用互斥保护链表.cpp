#include <algorithm>
#include <iostream>
#include <list>
#include <mutex>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value) {
    std::lock_guard<std::mutex> guard { some_mutex };
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
    std::lock_guard<std::mutex> guard { some_mutex };
    return std::find(begin(some_list), end(some_list), value_to_find) != end(some_list);
}

int main(int argc, char *argv[]) {

    return 0;
}
