#include "fmt/core.h"
#include <algorithm>
#include <iostream>
#include <string>

// MARK: 惰性字符串拼接的栗子
template <typename... Strings>
class lazy_string_concat_helper;

template <typename LastString, typename... Strings>
class lazy_string_concat_helper<LastString, Strings...> {
private:
    LastString data;
    lazy_string_concat_helper<Strings...> tail;

public:
    lazy_string_concat_helper(LastString data, lazy_string_concat_helper<Strings...> tail)
        : data { data }, tail { tail } {}

    int size() const {
        return data.size() + tail.size();
    }

    template <typename It>
    void save(It end) const {
        auto const begin = end - data.size();
        std::copy(std::cbegin(data), std::cend(data), begin);
        tail.save(begin);
    }

    operator std::string() const {
        std::string result(size(), '\0');
        save(result.end());
        return result;
    }

    lazy_string_concat_helper<std::string, LastString, Strings...>
    operator+(std::string const &other) const {
        return lazy_string_concat_helper<std::string, LastString, Strings...> { other, *this };
    }
};

template <>
class lazy_string_concat_helper<> {
public:
    lazy_string_concat_helper() {}

    int size() const {
        return 0;
    }

    template <typename It>
    void save(It) const {}

    lazy_string_concat_helper<std::string> operator+(std::string const &other) const {
        return lazy_string_concat_helper<std::string> { other, *this };
    }
};

lazy_string_concat_helper<> lazt_concat;

int main(int argc, char *argv[]) {

    std::string name = "Jane";
    std::string surname = "Smith";

    std::string const fullname = lazt_concat + surname + ", " + name;
    fmt::print("{}\n", fullname);

    return 0;
}
