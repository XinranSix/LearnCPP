#include <vector>
#include <span>
#include <iostream>
#include <format>

template <typename Matcher, typename MatchHandler>
void findMatches(std::span<const int> values1, std::span<const int> values2, Matcher matcher,
                 MatchHandler handler) {
    if (values1.size() != values2.size()) {
        return;
    } // Both vectors must be same size.

    for (size_t i { 0 }; i < values1.size(); ++i) {
        if (matcher(values1[i], values2[i])) {
            handler(i, values1[i], values2[i]);
        }
    }
}

bool intEqual(int item1, int item2) {
    return item1 == item2;
}

bool bothOdd(int item1, int item2) {
    return item1 % 2 == 1 && item2 % 2 == 1;
}

class Handler {
public:
    void handleMatch(size_t position, int value1, int value2) {
        std::cout << std::format("Match found at position {} ({}, {})", position, value1, value2)
                  << std::endl;
    }
};

int main() {
    Handler handler;

    auto handlerLambda { [&handler](size_t position, int value1, int value2) {
        handler.handleMatch(position, value1, value2);
    } };

    std::vector values1 { 2, 5, 6, 9, 10, 1, 1 };
    std::vector values2 { 4, 4, 2, 9, 0, 3, 1 };
    std::cout << "Calling findMatches() using intEqual():" << std::endl;
    findMatches(values1, values2, intEqual, handlerLambda);

    std::cout << "Calling findMatches() using bothOdd():" << std::endl;
    findMatches(values1, values2, bothOdd, handlerLambda);

    return 0;
}
