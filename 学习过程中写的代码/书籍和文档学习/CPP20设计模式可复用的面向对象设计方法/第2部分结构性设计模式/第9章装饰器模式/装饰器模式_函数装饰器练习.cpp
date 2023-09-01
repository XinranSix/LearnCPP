#include <functional>
#include <iostream>
#include <string>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <mutex>
#include <deque>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <memory>
#include <condition_variable>
#include <future>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <type_traits>

template <typename>
struct decorator;

template <typename R, typename... Args>
struct decorator<R(Args...)> {

    decorator(std::function<R(Args...)> func, std::string prev_info = "",
              std::string post_info = "")
        : m_func { func }, m_prev_info { std::move(prev_info) },
          m_post_info { std::move(post_info) } {}

    R operator()(Args... args) {
        std::cout << m_prev_info;
        R result { fun(args...) };
        std::cout << m_post_info;
        return result;
    }

private:
    std::function<R(Args...)> m_func;
    std::string m_prev_info;
    std::string m_post_info;
};

template <typename R, typename... Args>
auto meke_decorator(R (*func)(Args...), std::string &name) {
    return decorator<R(Args...)> { std::function<R(Args...)> { func }, name };
}

int main(int argc, char *argv[]) { return 0; }
