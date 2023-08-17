#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <iostream>
#include <gtest/gtest.h>
#include <span>
#include <vector>

TEST(find和find_if算法, find算法) {
#if 0
    std::vector<int> myVector;
    while (true) {
        std::cout << "Enter a number to add (0 to stop): ";
        int number {};
        std::cin >> number;
        if (number == 0) {
            break;
        }
        myVector.push_back(number);
    }

    while (true) {
        std::cout << "Enter a number to lookup (0 to stop): ";
        int number {};
        std::cin >> number;
        if (number == 0) {
            break;
        }
        auto endIt = cend(myVector);

        if (auto it = std::find(cbegin(myVector), endIt, number); it == endIt) {
            std::cout << "Could not find " << number << std::endl;
        } else {
            std::cout << "Found " << *it << std::endl;
        }
    }
#endif
}

bool perfectScore(int num) {
    return (num >= 100);
}

TEST(find和find_if算法, find_if算法) {
#if 0
    std::vector<int> myVector;
    while (true) {
        std::cout << "Enter a number to add (0 to stop): ";
        int number {};
        std::cin >> number;
        if (number == 0) {
            break;
        }
        myVector.push_back(number);
    }

    while (true) {
        std::cout << "Enter a number to lookup (0 to stop): ";
        int number {};
        std::cin >> number;
        if (number == 0) {
            break;
        }
        auto endIt = cend(myVector);

        // if (auto it = std::find_if(cbegin(myVector), endIt, perfectScore); it == endIt) {
        if (auto it = std::find_if(cbegin(myVector), endIt, [](int i) { return i >= 100; });
            it == endIt) {
            std::cout << "No perfect scores" << number << std::endl;
        } else {
            std::cout << "Found a \"perface\" score of" << *it << std::endl;
        }
    }
#endif
}

double airthmeticMean(std::span<const int> values) {
    double sum { std::accumulate(cbegin(values), cend(values), 0.0) };
    return sum / values.size();
}

int product(int value1, int value2) {
    return value1 * value2;
}

double geomtricMean(std::span<const int> values) {
    // int mult { std::accumulate(cbegin(values), cend(values), 1, product) };
    // int mult { std::accumulate(cbegin(values), cend(values), 1, [](int value1,int value2){return
    // value1*value2;}) };
    int mult { std::accumulate(cbegin(values), cend(values), 1, std::multiplies<> {}) };
    return std::pow(mult, 1.0 / values.size());
}

TEST(find和find_if算法, accumulate算法) {}

TEST(find和find_if算法, 算法回调) {
    auto isPerfectScore { [tally = 0](int i) mutable {
        std::cout << ++tally << std::endl;
        return i >= 100;
    } };

    std::vector<int> myVector;
    auto endIt { cend(myVector) };
    auto it { std::find_if(cbegin(myVector), endIt, isPerfectScore) };
    if (it != endIt) {
        std::cout << "Found a \"perfact\" score of " << *it << std::endl;
    }
    isPerfectScore(1);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
