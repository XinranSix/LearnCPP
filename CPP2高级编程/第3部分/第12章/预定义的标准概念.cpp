#include <iostream>
#include <concepts>

struct Foo {};

template <typename T>
concept IsDerivedFromFoo = std::derived_from<T, Foo>;

template <typename T>
concept IsConvertibleToBool = std::convertible_to<T, bool>;

template <typename T>
concept DefaultAndCopyConstructible =
    std::default_initializable<T> && std::copy_constructible<T>;

int main(int argc, char *argv[]) {
    return 0;
}
