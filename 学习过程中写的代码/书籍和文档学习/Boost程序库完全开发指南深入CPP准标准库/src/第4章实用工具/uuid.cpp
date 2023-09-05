#include <algorithm>
#include <cstring>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "boost/uuid/name_generator.hpp"
#include "boost/uuid/nil_generator.hpp"
#include "boost/uuid/random_generator.hpp"
#include "boost/uuid/string_generator.hpp"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"

using namespace boost::uuids;

TEST(uuid, 用法1) {

    uuid u;
    assert(uuid::static_size() == 16);
    assert(u.size() == 16);

    std::vector<unsigned char> v(16, 7);
    std::copy(begin(v), end(v), u.begin());
    assert(u.data[0] == u.data[1] && u.data[15] == 7);

    std::cout << u << std::endl;
    std::fill_n(u.data + 10, 6, 8);

    std::cout << u << std::endl;
}

TEST(uuid, 用法2) {
    uuid u;

    std::fill_n(u.begin(), u.size(), 0xab);
    assert(!u.is_nil());
    assert(u.variant() == u.variant_rfc_4122);
    assert(u.version() == u.version_unknown);
    std::cout << u << std::endl;

    std::memset(u.data, 0, 16);
    assert(u.is_nil());

    uuid u1, u2;

    std::fill_n(u1.begin(), u1.size(), 0xab);
    std::fill_n(u2.begin(), u2.size(), 0x10);

    assert(u1 != u2 && u1 > u2);

    u2.data[0] = 0xff;
    assert(u1 < u2);

    std::memset(u1.data, 0, 16);
    std::memset(u2.data, 0, 16);
    assert(u1 == u2);
}

/*
生成器
uuid库提供了四种生成器，分别是Nil生成器、字符串生成器、名字生成器和随机生成器。
它们都是函数对象，重载了operator()，可以直接调用它们生成uuid对象
*/
TEST(uuid, Nil生成器) {
    uuid u { nil_generator()() };
    assert(u.is_nil());
    u = nil_uuid();
    assert(u.is_nil());
}

TEST(uuid, 字符串生成器) {
    string_generator sgen {};
    uuid u1 { sgen("0123456789abcdef0123456789abcdef") };
    std::cout << u1 << std::endl;

    uuid u2 { sgen("01234567-89ab-cdef-0123-456789abcdef") };
    std::cout << u2 << std::endl;

    uuid u3 { sgen(L"{01234567-89ab-cdef-0123-456789abcdef}") };
    std::cout << u3 << std::endl;
}

TEST(uuid, 名字生成器) {
    uuid www_xxx_com { string_generator {}(
        "0123456789abcdef0123456789abcdef") };
    name_generator ngen { www_xxx_com };

    uuid u1 { ngen("mario") };
    assert(!u1.is_nil() && u1.version() == uuid::version_name_based_sha1);

    uuid u2 { ngen("link") };
    std::cout << u2 << std::endl;
}

TEST(uuid, 随机生成器) {
    random_generator rgen;

    uuid u { rgen() };
    assert(u.version() == uuid::version_random_number_based);
    std::cout << u << std::endl;
}

class uuid_t : public uuid {
private:
    static random_generator &rand_uuid() {
        static random_generator gen;
        return gen;
    }

    static string_generator &string_uuid() {
        static string_generator gen;
        return gen;
    }

public:
    uuid_t() : uuid { rand_uuid()() } {}
    uuid_t(int) : uuid { nil_uuid() } {}

    uuid_t(const char *str) : uuid { string_uuid()(str) } {}

    uuid_t(const uuid &u, const char *str)
        : uuid { name_generator { u }(str) } {}

    explicit uuid_t(const uuid &u) : uuid { u } {}

    operator uuid() { return static_cast<uuid &>(*this); }

    operator uuid() const { return static_cast<const uuid &>(*this); }
};

TEST(uuid, 增强用法) {
    uuid_t u0 { 0 };
    assert(u0.is_nil());

    uuid_t u1, u2;
    std::cout << u1 << std::endl;
    std::cout << u2 << std::endl;

    uuid_t u3 { "{01234567-89ab-cdef-0123-456789abcdef}" };
    std::cout << u3 << std::endl;

    std::cout << uuid_t { u3, "test name gen" } << std::endl;
}

TEST(uuid, 转换字符串) {
    uuid u { string_generator {}("01234567-89ab-cdef-0123-456789abcdef") };

    std::string str = to_string(u);
    std::cout << str << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
