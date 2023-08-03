#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

int main() {

    std::vector<std::string> strings;
    strings.push_back("Boost");
    strings.push_back("C++");
    strings.push_back("Libraries");

    std::vector<int> sizes;

    // for (std::vector<std::string>::iterator it = strings.begin();
    //      it != strings.end(); ++it) {
    //     sizes.push_back(it->size());
    // }

    std::for_each(
        strings.begin(), strings.end(),
        [&sizes](const std::string &str) { sizes.push_back(str.size()); });

    // for (std::vector<int>::iterator it = sizes.begin(); it != sizes.end();
    //      ++it) {
    //     std::cout << *it << std::endl;
    // }

    std::for_each(sizes.begin(), sizes.end(),
                  [](const int &i) { std::cout << i << std::endl; });

    return 0;
}