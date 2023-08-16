#include <format>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <ranges>
#include <ostream>
#include <iterator>

template <typename InputIter, typename OutputIter>
void myCopy(InputIter begin, InputIter end, OutputIter target) {
    for (auto iter { begin }; iter != end; ++iter, ++target) {
        *target = *iter;
    }
}

int main(int argc, char *argv[]) {

    std::vector<int> values;

    for (auto value : std::ranges::istream_view<int> { std::cin } |
                          std::views::take_while([](auto const &v) { return v != -1; })) {
        values.push_back(value);
    }

    myCopy(begin(values), end(values), std::ostream_iterator<int> { std::cout, " " });

    std::cout << std::endl;

    return 0;
}
