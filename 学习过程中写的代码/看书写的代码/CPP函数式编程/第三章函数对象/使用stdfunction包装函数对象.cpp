#include <cmath>
#include <iostream>
#include <functional>
#include <boost/phoenix/phoenix.hpp>

int main(int argc, char *argv[]) {

    float x { 0.5 };

    std::function<float(float, float)> test_function;
    test_function = std::fmaxf;
    test_function = std::multiplies<float> {};
    test_function = std::multiplies<> {};
    test_function = [x](float a, float b) { return a * x + b; };
    test_function = [x](auto a, auto b) { return a * x + b; };
    using namespace boost::phoenix::placeholders;
    test_function = (arg1 + arg2) / 2;
    // test_function = [](std::string s) { return s.empty(); } // Error

    std::string str { "HYT" };
    std::function<bool(std::string)> f;
    f = &std::string::empty;

    std::cout << f(str) << "\n";

    return 0;
}
