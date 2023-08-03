#include <boost/signals2.hpp>
#include <iostream>
#include <algorithm>

int func1() { return 1; }

int func2() { return 2; }

template<typename T>
struct min_element {
    using result_type = T;

    template<typename InputIterator>
    T operator()(InputIterator first, InputIterator last) const {
        return *std::min_element(first, last);
    }
};

int main() {

    boost::signals2::signal<int(), min_element<int>> s;
    s.connect(func1);
    s.connect(func2);
    std::cout << s() << std::endl;

    return 0;
}
