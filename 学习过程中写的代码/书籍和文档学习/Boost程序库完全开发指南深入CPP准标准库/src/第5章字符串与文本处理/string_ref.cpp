#include <cstring>
#include <iostream>
#include <gtest/gtest.h>
#include <ostream>
#include <string>
#include "boost/utility/string_ref.hpp"
#include "boost/utility/string_ref_fwd.hpp"

TEST(string_ref, 用法1) {
    const char *ch = "Days of Future Fasy";
    std::string str { ch };

    boost::string_ref s1 { ch };
    boost::string_ref s2 { str };
    assert(s1 == s2 && s1 == ch && s2 == str);

    boost::string_ref s3 { ch, 4 };
    assert(s3 == str.substr(0, 4));

    boost::string_ref s4, s5;

    s4 = ch;
    s5 = str;

    assert(s4 == s5);
}

TEST(string_ref, 用法2) {
    const char *ch = "Apple iPhone iPad";

    boost::string_ref str { ch };

    assert(!str.empty());
    assert(str.size() == strlen(ch));

    for (auto &x : str) {
        std::cout << x;
    }
    std::endl(std::cout);

    assert(str.front() == 'A');
    assert(str[1] == 'p');

    assert(str.find('i' == 6));

    auto substr { str.substr(6, 6) };
    assert(substr == "iPhone");

    std::string s { str.to_string() };
    assert(str == s);

    str.clear();
    assert(str.empty());
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
