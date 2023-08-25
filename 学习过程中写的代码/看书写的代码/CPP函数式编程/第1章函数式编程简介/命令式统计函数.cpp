#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> count_lines_in_files(std::vector<std::string> const &files) {
    std::vector<int> results;
    char c { 0 };
    for (auto const &file : files) {
        int line_count { 0 };
        std::ifstream in { file };
        while (in.get(c)) {
            if (c == '\n') {
                line_count++;
            }
        }
        results.emplace_back(line_count);
    }
    return results;
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

    std::for_each(cbegin(results), cend(results),
                  [](auto const &line) { std::cout << line << std::endl; });

    return 0;
}
