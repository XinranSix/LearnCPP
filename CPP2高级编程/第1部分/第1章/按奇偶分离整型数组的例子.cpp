#include <iostream>
#include <array>
#include <format>
#include <vector>
#include <compare>
#include <utility>
#include <optional>

struct OddsAndEvens {
    std::vector<int> odds, evens;
};

OddsAndEvens separateOddsAndEvens(const std::vector<int> &arr) {
    std::vector<int> odds, evens;
    for (int i : arr) {
        if (i % 2 == 1) {
            odds.push_back(i);
        } else {
            evens.push_back(i);
        }
    }
    return {.odds = odds, .evens = evens};
}

int main(int arvc, char *argv[]) {

    std::vector<int> vecUnSplit{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto oddsAndEvens{separateOddsAndEvens(vecUnSplit)};

    return 0;
}
