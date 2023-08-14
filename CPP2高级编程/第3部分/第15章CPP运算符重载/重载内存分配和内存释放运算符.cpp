#include <cstddef>
#include <exception>
#include <iostream>
#include <gtest/gtest.h>
#include <new>

class MemoryDemo {
public:
    virtual ~MemoryDemo() = default;

    // MemoryDemo() {
    //     throw std::exception {};
    // }

    void *operator new(size_t size);
    // void operator delete(void *ptr) noexcept;
    void operator delete(void *ptr, size_t size) noexcept;

    void *operator new[](size_t size);
    void operator delete[](void *ptr) noexcept;

    void *operator new(size_t size, std::nothrow_t const &) noexcept;
    void operator delete(void *ptr, std::nothrow_t const &) noexcept;

    void *operator new[](size_t size, std::nothrow_t const &) noexcept;
    void operator delete[](void *ptr, std::nothrow_t const &) noexcept;

public:
    void *operator new(size_t size, int extra);
    void operator delete(void *ptr, int extra) noexcept;
};

void *MemoryDemo::operator new(size_t size) {
    std::cout << "operator new" << std::endl;
    return ::operator new(size);
}

// void MemoryDemo::operator delete(void *ptr) noexcept {
//     std::cout << "operator delete" << std::endl;
//     ::operator delete(ptr);
// }

void MemoryDemo::operator delete(void *ptr, size_t size) noexcept {
    std::cout << "operator delete with size " << size << std::endl;
    ::operator delete(ptr);
}

void *MemoryDemo::operator new[](size_t size) {
    std::cout << "operator new[]" << std::endl;
    return ::operator new[](size);
}

void MemoryDemo::operator delete[](void *ptr) noexcept {
    std::cout << "operator delete[]" << std::endl;
    ::operator delete[](ptr);
}

void *MemoryDemo::operator new(size_t size, std::nothrow_t const &) noexcept {
    std::cout << "operator new nothrow" << std::endl;
    return ::operator new(size, std::nothrow);
}

void MemoryDemo::operator delete(void *ptr, std::nothrow_t const &) noexcept {
    std::cout << "operator delete nothrow" << std::endl;
    ::operator delete(ptr, std::nothrow);
}

void *MemoryDemo::operator new[](size_t size, std::nothrow_t const &) noexcept {
    std::cout << "operator new[] nothrow" << std::endl;
    return ::operator new[](size, std::nothrow);
}

void MemoryDemo::operator delete[](void *ptr, std::nothrow_t const &) noexcept {
    std::cout << "operator delete[] nothrow" << std::endl;
    ::operator delete[](ptr, std::nothrow);
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

void *MemoryDemo::operator new(size_t size, int extra) {
    std::cout << "operator new with extra int: " << extra << std::endl;
    return ::operator new(size);
}

void MemoryDemo::operator delete(void *ptr, int extra) noexcept {
    std::cout << "operator delete with extra int: " << extra << std::endl;
    return ::operator delete(ptr);
}

TEST(重载内存分配和内存释放运算符,
     重载带有额外参数的operator_new和operator_delete) {
    MemoryDemo *memp { new (5) MemoryDemo {} };
    delete memp;
}

TEST(重载内存分配和内存释放运算符, 重载带有内存大小参数的operator_delete) {}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
