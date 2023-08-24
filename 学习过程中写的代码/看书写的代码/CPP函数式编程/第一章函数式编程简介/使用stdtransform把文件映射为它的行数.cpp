#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <type_traits>
#include <vector>

int count_lines(std::string const &filename) {
    std::ifstream in { filename };
    return std::count(std::istreambuf_iterator<char> { in }, std::istreambuf_iterator<char> {},
                      '\n');
}

std::vector<int> count_lines_in_files(std::vector<std::string> const &files) {
    std::vector<int> results(files.size());

    std::transform(cbegin(files), cend(files), results.begin(), count_lines);
    // return files | std::ranges::views::transform(count_lines);

    return results;
}

int main(int argc, char *argv[]) {

    using namespace std;
    std::vector<std::string> files {
        "./函数式求平均值.cpp"s,
        "./使用stdaccumulate实现统计行数.cpp"s,
        "./函数式求平均值并行算法.cpp"s,
        "./计算所有得分的积.cpp"s,

    };

    auto results { count_lines_in_files(files) };

    std::for_each(cbegin(results), cend(results),
                  [](auto const &line) { std::cout << line << std::endl; });

    return 0;
}
