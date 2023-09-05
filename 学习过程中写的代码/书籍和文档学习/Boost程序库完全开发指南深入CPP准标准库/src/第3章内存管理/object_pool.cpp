#include <iostream>
#include <string>
#include <utility>
#include "boost/pool/object_pool.hpp"

struct demo_class {
public:
    int a {}, b {}, c {};

    demo_class(int x = 1, int y = 2, int z = 3) : a { x }, b { y }, c { z } {}
};

template <typename P, typename... Args>
inline typename P::element_type *consturct(P &p, Args &&...args) {
    typename P::element_type *mem = p.malloc();

    assert(mem != 0);
    new (mem) typename P::element_type(std::forward<Args>(args)...);

    return mem;
}

struct demo_class1 {
    demo_class1(int, int, int, int) {
        std::cout << "demo_class1 ctor" << std::endl;
    }

    ~demo_class1() { std::cout << "demo_class1 dtor" << std::endl; }
};

int main(int argc, char *argv[]) {
    {
        boost::object_pool<demo_class> p1;

        auto p { p1.malloc() };
        assert(p1.is_from(p));

        assert(p->a != 1 || p->b != 2 || p->c != 3);

        p = p1.construct(7, 8, 9);
        assert(p->a == 7);

        boost::object_pool<std::string> pls;
        for (int i { 0 }; i < 10; ++i) {
            std::string *ps { pls.construct("hello, object_pool") };
            std::cout << *ps << std::endl;
        }
    }

    // 更多的参数
    {
        boost::object_pool<demo_class1> p1;
        auto d { consturct(p1, 1, 2, 3, 4) };
    }

    return 0;
}
