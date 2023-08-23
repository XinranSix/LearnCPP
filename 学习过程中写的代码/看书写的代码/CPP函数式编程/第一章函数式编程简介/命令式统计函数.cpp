#include <fstream>
#include <iostream>
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

    return 0;
}
