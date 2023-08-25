#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <gtest/gtest.h>
#include <map>
#include <ostream>
#include <random>
#include <vector>

int getRandom(int min, int max) {
    return static_cast<int>(rand() % (max + 1UL - min)) + min;
}

TEST(随机数工具, C风格随机数生成器) {
    srand(static_cast<unsigned int>(time(nullptr)));
    std::cout << rand() << std::endl;
}

/* -------------------------------------------------------------------------- */

TEST(随机数工具, 随机数引擎之random_device) {
    std::random_device rnd;
    std::cout << "Entropy: " << rnd.entropy() << std::endl;
    std::cout << "Min value: " << rnd.min() << ", Max value: " << rnd.max() << std::endl;
    std::cout << "Random number: " << rnd() << std::endl;
}

void fillVector(std::vector<int> &values, auto const &generator) {
    std::generate(begin(values), end(values), generator);
}

TEST(随机数工具, 生成随机数) {
    std::random_device seeder;
    const auto seed { seeder.entropy() ? seeder() : time(nullptr) };
    std::mt19937 engine { static_cast<std::mt19937::result_type>(seed) };

    std::uniform_int_distribution<int> distribution { 1, 99 };
    std::cout << distribution(engine) << std::endl;

    auto generator { std::bind(distribution, engine) };
    std::vector<int> values(10);
    // std::generate(begin(values), end(values), generator);
    fillVector(values, generator);
    for (auto i : values) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

TEST(随机数工具, 生成随机数1) {
    const unsigned int Start { 1 };
    const unsigned int End { 99 };
    const unsigned int Iterations { 1'000'000 };

    std::random_device seeder;
    const auto seed { seeder.entropy() ? seeder() : time(nullptr) };
    std::mt19937 engine { static_cast<std::mt19937::result_type>(seed) };
    std::uniform_int_distribution<int> distribution { Start, End };
    auto generator { std::bind(distribution, engine) };
    std::map<int, int> histogram;
    for (unsigned int i { 0 }; i < Iterations; ++i) {
        int randomNumber { generator() };
        ++(histogram[randomNumber]);
    }
    std::ofstream of { "res.csv" };
    for (unsigned int i { Start }; i < End; ++i) {
        of << i << "," << histogram[i] << std::endl;
    }
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
