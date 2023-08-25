#include <format>
#include <iostream>
#include <iterator>
#include <vector>

double average_score(std::vector<int> const &scores) {
    int sum { 0 };
    for (int score : scores) {
        sum += score;
    }
    return sum / (double)scores.size();
}

int main(int argc, char *argv[]) {

    auto out { std::ostream_iterator<char> { std::cout } };

    std::vector<int> scores { 9, 7, 10, 5, 8, 8, 6 };

    std::format_to(out, "{:.2}\n", average_score(scores));

    return 0;
}
