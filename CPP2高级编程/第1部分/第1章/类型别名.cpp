#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

void procressVector(const std::vector<std::basic_string<char>> &vec) {}

int main(int arvc, char *argv[]) {

    using IntPtr = int *;

    int *p1;
    IntPtr p2;

    std::cout << std::is_same_v<int *, IntPtr> << std::endl;

    std::vector<std::basic_string<char>> myVector;
    procressVector(myVector);

    typedef int *IntPtr1;

    return 0;
}
