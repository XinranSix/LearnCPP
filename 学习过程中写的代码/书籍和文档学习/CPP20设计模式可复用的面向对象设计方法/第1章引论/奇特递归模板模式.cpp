#include <iostream>

template <typename Derived>
struct SomeBase {
    void foo() {
        for (auto &item : *static_cast<Derived *>(this)) {}
    }
};

struct Foo : SomeBase<Foo> {};

struct MyClass : SomeBase<Foo> {
    class iterator {};

    iterator begin() const { return iterator {}; }
    iterator end() const { return iterator {}; }
};

int main(int argc, char *argv[]) { return 0; }
