#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "boost/assign.hpp"
#include "yj/tools/output_container.h"

using namespace boost::assign;

int main(int argc, char *argv[]) {

    std::vector<int> v;
    v += 1, 2, 3, 4, 5, 6 * 6;
    std::cout << v << std::endl;

    std::set<std::string> s;
    s += "c", "cpp", "lua", "swift";
    std::cout << s << std::endl;

    std::map<int, std::string> m;
    m += std::make_pair(1, "one"), std::make_pair(2, "two");
    std::cout << m << std::endl;

    return 0;
}
