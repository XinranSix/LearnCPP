#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {

    int count = 0;
    std::vector<std::string> words { "An", "ancient", "pond" };

    std::for_each(cbegin(words), cend(words), [count](auto const &word) mutable {
        if (std::isupper(word[0])) {
            std::cout << word << " " << count << std::endl;
            ++count;
        }
    });

    std::cout << count << std::endl;

    return 0;
}
