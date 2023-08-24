#include <algorithm>
#include <bits/ranges_algo.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>
#include <ranges>

int count_lines(std::string const &filename) {
    std::ifstream in { filename };
    return std::count(std::istreambuf_iterator<char> { in }, std::istreambuf_iterator<char> {},
                      '\n');
}

auto count_lines_in_files(std::vector<std::string> const &files) {
    std::vector<int> results(files.size());

    return files | std::ranges::views::transform(count_lines);
}

int main(int argc, char *argv[]) {

    using namespace std;
    std::vector<std::string> files {
        "./命令式统计函数.cpp"s,
        "./使用stdtransform把文件映射为它的行数.cpp"s,
        "./使用stdcount统计换行符数目.cpp"s,
        "./使用range进行转换.cpp"s,

    };

    auto results { count_lines_in_files(files) };

    std::ranges::for_each(results, [](auto line) { std::cout << line << std::endl; });

    return 0;
}

