#include "boost/smart_ptr/intrusive_ptr.hpp"
#include "boost/smart_ptr/weak_ptr.hpp"
#include "boost/smart_ptr/intrusive_ref_counter.hpp"
#include <iostream>
#include <gtest/gtest.h>

/*
intrusive_ptr 也是一种引用计数型智能指针，但与之前介绍的
scoped_ptr 和shared_ptr不同，需要额外增加一些代码才能使用它。
它的名字可能会给人造成误解，实际上它并不一定要“侵入”代理对
象的内部修改数据。
*/

struct counted_data {
    int m_count { 0 };
};

void intrusive_ptr_add_ref(counted_data *p) { ++p->m_count; }

void intrusive_ptr_release(counted_data *p) {
    if (--p->m_count == 0) {
        delete p;
    }
}

TEST(intrusive_ptr, 用法) {
    using counted_ptr = boost::intrusive_ptr<counted_data>;

    counted_ptr p { new counted_data };
    assert(p);
    assert(p->m_count == 1);

    counted_ptr p2 { p };
    assert(p->m_count == 2);

    counted_ptr weak_p { p.get(), false };
    assert(weak_p->m_count == 2);

    p2.reset();
    assert(!p2);
    assert(p->m_count == 1);
}

struct counted_data1 : public boost::intrusive_ref_counter<counted_data1> {
   
};

TEST(intrusive_ptr, 引用计数器) {
    using counted_ptr = boost::intrusive_ptr<counted_data1>;

    counted_ptr p { new counted_data1 };
    assert(p);
    assert(p->use_count() == 1);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
