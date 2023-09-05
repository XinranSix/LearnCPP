#include <iostream>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "boost/smart_ptr.hpp"
#include "boost/smart_ptr/scoped_ptr.hpp"
#include "boost/smart_ptr/make_unique.hpp"

// scoped_ptr 是一个与auto_ptr/unique_ptr 很类似的智能指针，
// 它包装了new操作符在堆上分配的动态对象，能够保证动态创建的对象
// 在任何时候都可以被正确地删除。但scoped_ptr的所有权更加严格，
// 不能转让，一旦scoped_ptr获取了对象的管理权，我们就无法再从它
// 那里收回来。

// 这个智能指针只能在本作用域里使用，不希望被转让

TEST(scoped_ptr, 基本操作1) {
    boost::scoped_ptr<std::string> sp { new std::string { "text" } };

    assert(sp);
    assert(sp != nullptr);

    std::cout << *sp << std::endl;
    std::cout << sp->size() << std::endl;

    // boost::scoped_ptr<std::string> sp2 { sp }; // 禁止 copy
    // boost::scoped_ptr<std::string> sp2 { std::move(sp) }; // 禁止 move
}

struct posix_file {
    posix_file(const char *file_name) {
        std::cout << "open file: " << file_name << std::endl;
    }

    ~posix_file() { std::cout << "close file" << std::endl; }
};

TEST(scoped_ptr, 基本操作2) {
    boost::scoped_ptr<posix_file> fp { new posix_file { "/tmp/a.txt" } };

    boost::scoped_ptr<int> p { new int };

    if (p) {
        *p = 100;
        std::cout << *p << std::endl;
    }

    p.reset();

    assert(p == 0);
    if (!p) {
        std::cout << "scoped_ptr == nullptr" << std::endl;
    }
}

TEST(scoped_ptr, 对比标准) {
    // 可以毫不犹豫地使用unique_ptr 来代替scoped_ptr
    // 当然，scoped_ptr也有它的优点，它只专注于做好作用域内的指针管理工作，含义明确，而且不允许转让指针的所有权
    std::unique_ptr<int> up { new int };

    assert(up);
    *up = 10;
    std::cout << *up << std::endl;

    up.reset();
    assert(!up);
}

TEST(scoped_ptr, make_unique) {
    /*
    C++11标准虽然定义了unique_ptr，但却“遗忘”了对应的工厂函
    数make_unique()（C++14 标准补上了这个漏洞），
    于是boost.smart_ptr库特意在头文件＜boost/smart_ptr/make_unique.hpp＞里实现
    了make_unique()函数，
    */

    auto p { boost::make_unique<int>(10) };

    assert(p && *p == 10);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
