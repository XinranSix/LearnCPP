#include <algorithm>
#include <functional>
#include <iostream>
#include <numbers>
#include <utility>
#include <fmt/core.h>
#include <vector>

template <typename Function, typename SecondArgType>
class partial_application_on_2nd_impl {
public:
    partial_application_on_2nd_impl(Function function, SecondArgType second_arg)
        : m_function { function }, m_second_arg { second_arg } {}

    template <typename FirstArgType>
    auto operator()(FirstArgType &&first_arg) -> decltype(auto) {
        return m_function(std::forward<FirstArgType>(first_arg), m_second_arg);
    }

private:
    Function m_function;
    SecondArgType m_second_arg;
};

template <typename Function, typename SecondArgType>
partial_application_on_2nd_impl<Function, SecondArgType> bind2nd(Function &&function,
                                                                 SecondArgType &&second_arg) {
    return partial_application_on_2nd_impl<Function, SecondArgType> {
        std::forward<Function>(function), std::forward<SecondArgType>(second_arg)
    };
}

int main(int argc, char *argv[]) {

    auto greater_than_42 = bind2nd(std::greater<int>(), 42);

    std::vector<int> xs { 274, 234, 745, 213, 356, 12, 4, 6, 1, 61, 356, 1, 34, 12 };

    fmt::print("{}\n", greater_than_42(1));
    fmt::print("{}\n", greater_than_42(50));

    std::partition(begin(xs), end(xs), bind2nd(std::greater<int> {}, 6));
    std::for_each(cbegin(xs), cend(xs), [](auto v) { fmt::print("{} ", v); });
    fmt::print("\n");

    std::vector<double> degrees { 0, 30, 45, 60 };
    std::vector<double> radians(degrees.size());

    std::transform(cbegin(degrees), cend(degrees), begin(radians),
                   bind2nd(std::multiplies<double> {}, std::numbers::pi_v<double> / 180.0));

    std::for_each(cbegin(radians), cend(radians), [](auto rad) { fmt::print("{:.2} ", rad); });
    fmt::print("\n");
    std::for_each(cbegin(degrees), cend(degrees), [](auto deg) { fmt::print("{:.2} ", deg); });
    fmt::print("\n");

    return 0;
}
