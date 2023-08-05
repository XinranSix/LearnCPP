#include <format>
#include <iostream>
#include <vector>

int main(int arvc, char *argv[]) {

    std::vector<int> myVector{11, 22};

    myVector.push_back(33);
    myVector.push_back(44);

    std::cout << std::format("1st element: {}", myVector[0]) << std::endl;

    std::vector v{1};

    return 0;
}
