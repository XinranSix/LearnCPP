#include "fmt/core.h"
#include <iostream>
#include <map>
#include <tuple>

// MARK: 通用记忆化的一个栗子
template <typename Result, typename... Args>
auto make_memoized(Result (*f)(Args...)) {
    std::map<std::tuple<Args...>, Result> cache;

    return [f, cache](Args... args) mutable -> Result {
        auto const args_tuple { std::make_tuple(args...) };
        auto const cached { cache.find(args_tuple) };

        if (cached == cache.end()) {
            auto result { f(args...) };
            cache[args_tuple] = result;
            return result;
        } else {
            return cached->second;
        }
    };
}

unsigned int fib(unsigned int n) {
    return n == 0 ? 0 : n == 1 ? 1 : fib(n - 1) + fib(n - 2);
}

int main(int argc, char *argv[]) {

    auto fibmemo = make_memoized(fib);

    fmt::print("{}\n", fibmemo(15));
    fmt::print("{}\n", fibmemo(15));

    return 0;
}
