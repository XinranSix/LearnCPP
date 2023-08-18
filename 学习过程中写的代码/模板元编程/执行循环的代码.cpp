#include <iostream>

template<size_t Input>
const size_t OnesCount = (Input % 2) + OnesCount<Input / 2>;

template<>
constexpr size_t OnesCount<0> = 0;

template<size_t... Inputs>
constexpr size_t Accumulate = 0;

template<size_t CurInput, size_t... Inputs>
constexpr size_t Accumulate<CurInput, Inputs...> =
    CurInput + Accumulate<Inputs...>;

// 折叠表达式的做法
template<size_t... values>
constexpr size_t fun() {
    return (0 + ... + values);
}

int main(int arvc, char *argv[]) {

    constexpr size_t res = OnesCount<45>;
    std::cout << res << std::endl;

    constexpr size_t res1 = Accumulate<1, 2, 3, 4, 5>;
    std::cout << res1 << std::endl;

    constexpr size_t res2 = fun<1, 2, 3, 4, 5>();
    std::cout << res2 << std::endl;

    return 0;
}
