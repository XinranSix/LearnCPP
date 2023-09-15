#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include "boost/dynamic_bitset.hpp"
#include "boost/dynamic_bitset/dynamic_bitset.hpp"
#include "boost/utility/binary.hpp"

TEST(dynamic_bitset, 创建与赋值) {
    boost::dynamic_bitset<> db1;
    boost::dynamic_bitset<> db2 { 10 };
    boost::dynamic_bitset<> db3 { 0x16, BOOST_BINARY(10101) };
    boost::dynamic_bitset<> db4 { std::string { "0100" } };
    boost::dynamic_bitset<> db5 { db3 };

    boost::dynamic_bitset<> db6;
    db6 = db4;

    std::cout << std::hex << db5.to_ulong() << std::endl;
    std::cout << db4[0] << db4[1] << db4[2] << std::endl;
}

TEST(dynamic_bitset, 容器操作) {
    boost::dynamic_bitset<> db;

    db.resize(10, true);
    std::cout << db << std::endl;

    db.resize(5);
    std::cout << db << std::endl;

    boost::dynamic_bitset<> db1 { 5, BOOST_BINARY(01110) };

    std::cout << db1 << std::endl;
    assert(db1.size() == 5);

    db1.clear();
    assert(db1.empty() && db1.size() == 0);

    assert(boost::dynamic_bitset<>(64).num_blocks() == 1);
    assert(boost::dynamic_bitset<>(65).num_blocks() == 2);

    boost::dynamic_bitset<> db2 { 5, BOOST_BINARY(01001) };
    db2.push_back(true);
    assert(db2.to_ulong() == BOOST_BINARY_UL(101001));

    boost::dynamic_bitset<> db3 { 5, BOOST_BINARY(01001) };
    db3.append(BOOST_BINARY(101));
    assert(db3.size() == sizeof(unsigned long) * 8 + 5);
    std::cout << db3 << std::endl;
}

TEST(dynamic_bitset, 基本运算) {
    boost::dynamic_bitset<> db1 { 4, BOOST_BINARY(1010) };

    db1[0] &= 1;
    db1[1] ^= 1;
    std::cout << db1 << std::endl;

    boost::dynamic_bitset<> db2 { 4, BOOST_BINARY(0101) };
    assert(db1 > db2);

    std::cout << (db1 ^ db2) << std::endl;
    std::cout << (db1 | db2) << std::endl;
}

TEST(dynamic_bitset, 访问元素) {
    /*
    有4个测试二进制位的函数：
        ■ test() 函数检验第n位是否是1。
        ■ 如果容器中存在二进制位1，那么any() 返回true。
        ■ 如果容器中不存在二进制位1，那么none() 返回true。
        ■ count() 函数统计容器中所有值为1的元素的数量。
    */
    boost::dynamic_bitset<> db1 { 4, BOOST_BINARY(0101) };
    assert(db1.test(0) && !db1.test(1));
    assert(db1.any() && !db1.none());
    assert(db1.count() == 2);

    /*
    有3个反转二进制位的函数：
        ■ set() 函数可以置全部或特定位置的值为1或0。
        ■ reset() 可以置全部或特定位置的值为0。
        ■ flip() 可以反转全部或特定位置的值。
    */
    boost::dynamic_bitset<> db2 { 4, BOOST_BINARY(0101) };
    db2.flip();
    assert(db2.to_ulong() == BOOST_BINARY(1010));

    db2.set();
    assert(!db2.none());

    db2.reset();
    assert(!db2.any());

    db2.set(1, 1);
    assert(db2.count() == 1);

    /*
    dynamic_bitset还为访问元素提供了查找操作：
    ■ find_first() 从第0位开始查找，返回第一个值为1的位置。
    ■ find_next(pos) 则从第pos位开始查找，返回第一个值为1的位置；
       如果找不到这样的值，则返回npos。
    */
    boost::dynamic_bitset<> db3 { 5, BOOST_BINARY(00101) };
    auto pos { db3.find_first() };
    assert(pos == 0);

    pos = db3.find_next(pos);
    assert(pos == 2);
}

TEST(dynamic_bitset, 类型转换) {
    boost::dynamic_bitset<> db1 { 10, BOOST_BINARY(1010101) };
    std::cout << db1.to_ulong() << std::endl;
}

TEST(dynamic_bitset, 集合操作) {
    boost::dynamic_bitset<> db1 { 5, BOOST_BINARY(10101) };
    boost::dynamic_bitset<> db2 { 5, BOOST_BINARY(10010) };

    std::cout << (db1 | db2) << std::endl; // 并
    std::cout << (db1 & db2) << std::endl; // 交
    std::cout << (db1 - db2) << std::endl; // 差

    boost::dynamic_bitset<> db3 { 5, BOOST_BINARY(101) };
    assert(db3.is_proper_subset_of(db1));

    boost::dynamic_bitset<> db4 { db2 };

    assert(db4.is_subset_of(db2));
    assert(!db4.is_proper_subset_of(db2));
}

TEST(dynamic_bitset, 综合运用) {
    
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
