#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

int answer { 42 };

auto ask1() {
    return answer;
}

auto const &ask2() {
    return answer;
}

// auto ask(bool flag) {
//     if (flag) {
//         return 42;
//     } else {
//         return std::string { "42" };
//     }
// }

auto factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return factorial(n - 1) * n;
    }
}

decltype(auto) ask3() {
    return answer;
}

decltype(auto) ask4() {
    return (answer);
}

decltype(auto) ask5() {
    return 42 + answer;
}

template <typename Object, typename Function>
decltype(auto) call_on_object(Object &&object, Function function) {
    return function(std::forward<Object>(object));
}

int main(int argc, char *argv[]) {

    return 0;
}
