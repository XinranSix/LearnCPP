#include <iostream>
#include <memory>

class MyClass {};

int main(int argc, char *argv[]) {

    std::allocator<MyClass> alloc;
    auto *memory { alloc.allocate(1) };
    new (memory) MyClass();

    std::destroy_at(memory);
    alloc.deallocate(memory, 1);
    memory = nullptr;

    return 0;
}
