#include "boost/smart_ptr/scoped_ptr.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>
#include <iostream>

int main() {

    std::vector<boost::shared_ptr<int>> v;
    v.push_back(boost::shared_ptr<int>(new int(1)));
    v.push_back(boost::shared_ptr<int>(new int(2)));

    for (auto &i : v) {
        std::cout << i << std::endl;
    }

    boost::shared_ptr<int> i1(new int(1));
    boost::shared_ptr<int> i2(i1);
    i1.reset(new int(2));

    return 0;
}
