#include <iostream>
#include <memory>

struct Foo : public std::enable_shared_from_this<Foo> {
    std::shared_ptr<Foo> getPointer() { return shared_from_this(); }
};

int main(int argc, char *argv[]) {

    auto ptr1{std::make_shared<Foo>()};
    auto ptr2{ptr1->getPointer()};

    return 0;
}
