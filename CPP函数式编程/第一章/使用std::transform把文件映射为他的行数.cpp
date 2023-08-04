#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

int count_lines(std::string const &filename) {

    std::ifstream in{filename};

    return std::count(std::istreambuf_iterator<char>(in),
                      std::istreambuf_iterator<char>(), '\n');
}

std::vector<int> count_lines_in_files(std::vector<std::string> const &files) {

    std::vector<int> results;

    std::transform(files.cbegin(), files.cend(), results.begin(), count_lines);

    return results;
}

int main() { return 0; }
