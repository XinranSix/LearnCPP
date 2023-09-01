#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

struct Generator {
    virtual std::vector<int> generate(int const count) const {
        std::vector<int> result(count);
        std::generate(begin(result), end(result),
                      [&]() { return 1 + rand() % 9; });
        return result;
    }
};

struct Splitter {
    std::vector<std::vector<int>>
    split(std::vector<std::vector<int>> array) const {

        auto size { array.size() };

        std::vector<std::vector<int>> result(2 * size + 2,
                                             std::vector<int>(size));
        std::copy(begin(array), end(array), begin(result));
        for (int i { 0 }; i < size; ++i) {
            for (int j { 0 }; j < size; ++j) {
                result[i + size][j] = array[j][i];
            }
        }

        for (int i { 0 }; i < size; ++i) {
            result[2 * size][i] = array[i][i];
        }

        for (int i { 0 }; i < size; ++i) {
            result[2 * size + 1][i] = array[i][size - 1 - i];
        }

        return result;
    }
};

struct Verifier {
    bool verify(std::vector<std::vector<int>> array) const {
        if (array.empty()) {
            return false;
        }
        auto expected { std::accumulate(begin(array[0]), end(array[0]), 0) };
        return std::all_of(begin(array), end(array), [=](auto const &inner) {
            return std::accumulate(begin(inner), end(inner), 0) == expected;
        });
    }
};

template <typename G = Generator, typename S = Splitter, typename V = Verifier>
struct MagicSquareGenerator {
    std::vector<std::vector<int>> generate(int size) {
        G g;
        S s;
        V v;

        std::vector<std::vector<int>> square;

        do {
            square.clear();
            for (int i { 0 }; i < size; ++i) {
                square.emplace_back(g.generate(size));
            }
        } while (!v.verify(s.split(square)));

        return square;
    }
};

struct UniqueGenerator : Generator {
    std::vector<int> generate(int const count) const override {
        std::vector<int> result;
        do {
            result = Generator::generate(count);
        } while (std::set<int>(begin(result), end(result)).size() !=
                 result.size());
        return result;
    }
};

int main(int argc, char *argv[]) {

    MagicSquareGenerator gen;
    auto square { gen.generate(3) };

    for (int i { 0 }; i < square.size(); ++i) {
        for (int j { 0 }; j < square[i].size(); ++j) {
            std::cout << square[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    MagicSquareGenerator<UniqueGenerator> gen1;
    square = { gen1.generate(3) };
    for (int i { 0 }; i < square.size(); ++i) {
        for (int j { 0 }; j < square[i].size(); ++j) {
            std::cout << square[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
