#include <functional>
#include <iostream>
#include <format>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

double score_product(std::vector<int> const &scores) {
    return std::accumulate(cbegin(scores), cend(scores), 1, std::multiplies<>());
}

int main(int argc, char *argv[]) {

    auto out { std::ostream_iterator<char> { std::cout } };

    std::vector<int> scores { 9, 7, 10, 5, 8, 8, 6 };

    std::format_to(out, "{}\n", score_product(scores));

    return 0;
}
