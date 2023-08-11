#include <iostream>
#include <vector>
#include <ranges>

using namespace std;
using namespace std::views;

int main() {
    vector<int> vec{20, 1, 12, 4, 20, 3, 10, 1};

    auto even = [](const int &a) { return a % 2 == 0; };

    auto square = [](const int &a) { return a * a; };

    for (int i : std::views::take(
             std::views::transform(std::views::filter(vec, even), square), 2)) {
        std::cout << i << endl;
    }

    return 0;
}