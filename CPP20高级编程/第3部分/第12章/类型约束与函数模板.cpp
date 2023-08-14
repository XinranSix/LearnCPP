#include <concepts>
#include <iostream>
#include <type_traits>

template <std::convertible_to<bool> T>
void handle(T const &t) {
}

template <typename T>
concept Incrementable = requires(T x) {
    x++;
    ++x;
};

template <typename T>
concept Decrementable = requires(T x) {
    x++;
    ++x;
};

template <Incrementable T>
void process(T const &t) {
}

template <typename T>
    requires Incrementable<T>
void process1(T const &t) {
}

template <typename T>
    requires std::convertible_to<T, bool>
void process2(T const &t) {
}

template <typename T>
    requires requires(T x) {
        x++;
        ++x;
    }
void process3(T const &t) {
}

template <typename T>
    requires(sizeof(T) == 4)
void process4(T const &t) {
}

template <typename T>
    requires Incrementable<T> && Decrementable<T>
void process5(T const &t) {
}

template <typename T>
    requires std::is_arithmetic_v<T>
void process6(T const &t) {
}

template <typename T>
void process7(T const &t)
    requires Incrementable<T>
{
}

void process8(Incrementable auto const &t) {
}

int main(int argc, char *argv[]) {
    return 0;
}
