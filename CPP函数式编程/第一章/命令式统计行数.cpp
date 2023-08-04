#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<int> count_lines_in_files(std::vector<std::string> const &files) {

    std::vector<int> results{};

    char c{};

    for (const auto &file : files) {
        int line_count{};
        std::ifstream in{file};

        while (in.get(c)) {
            if (c == '\n') {
                line_count++;
            }
        }
        results.push_back(line_count);
    }
    return results;
}

int main(int arvc, char *argv[]) { return 0; }
