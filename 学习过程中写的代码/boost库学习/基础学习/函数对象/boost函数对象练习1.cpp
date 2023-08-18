#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

// class divide_by : public std::binary_function<int, int, int> {
// public:
//     int operator()(int n, int div) const { return n / div; }
// };

int divide_by(int n, int div) { return n / div; }

int main() {
    std::vector<int> numbers;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    // std::transform(numbers.begin(), numbers.end(), numbers.begin(),
    //                std::bind2nd(divide_by(), 2));

    std::transform(numbers.begin(), numbers.end(), numbers.begin(),
                   std::bind(divide_by, std::placeholders::_1, 2));

    // for (std::vector<int>::iterator it = numbers.begin(); it !=
    // numbers.end();
    //      ++it)
    //     std::cout << *it << std::endl;

    std::for_each(numbers.begin(), numbers.end(),
                  [](const int &i) { std::cout << i << std::endl; });

    return 0;
}
