#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {

    std::cout << "Hello World" << std::endl;

    std::vector<int> v { 1, 2, 3 };
    std::cout << v.capacity() << std::endl;
    v.push_back(4);
    std::cout << v.capacity() << std::endl;

    return 0;
}
