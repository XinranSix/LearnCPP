#include "boost/smart_ptr/enable_shared_from_this.hpp"
#include "boost/smart_ptr/make_shared_object.hpp"
#include "boost/smart_ptr/shared_ptr.hpp"
#include "boost/smart_ptr/weak_ptr.hpp"
#include <iostream>
#include <gtest/gtest.h>

TEST(weak_ptr, 用法) {
    boost::shared_ptr<int> sp { new int { 10 } };
    assert(sp.use_count() == 1);

    boost::weak_ptr<int> wp { sp };
    assert(wp.use_count() == 1);
    assert(!wp.empty());

    if (!wp.expired()) {
        boost::shared_ptr<int> sp2 = wp.lock();
        *sp2 = 100;
        assert(wp.use_count() == 2);
    }

    assert(wp.use_count() == 1);
    sp.reset();
    assert(wp.expired());
    assert(!wp.lock());
}

class self_shared : public boost::enable_shared_from_this<self_shared> {
public:
    self_shared(int n) : x { n } {}
    int x {};
    void print() { std::cout << "self_shared: " << x << std::endl; }
};

TEST(weak_ptr, 对象自我管理) {
    auto sp { boost::make_shared<self_shared>(313) };
    sp->print();

    auto p { sp->shared_from_this() };
    p->x = 1000;
    p->print();
}

class node {
public:
    ~node() { std::cout << "deleted" << std::endl; }

    using ptr_type = boost::shared_ptr<node>;
    // using ptr_type = boost::weak_ptr<node>;
    ptr_type next;
};

TEST(weak_ptr, 打破循环引用) {
    {
        auto p1 { boost::make_shared<node>() };
        auto p2 { boost::make_shared<node>() };

        p1->next = p2;
        p2->next = p1;

        assert(p1.use_count() == 2);
        assert(p2.use_count() == 2);
    } // 退出作用域也不会释放 p1 和 p2 所管理的指针或资源
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
