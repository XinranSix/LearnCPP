#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <iterator>
#include <set>
#include <vector>

template <typename IteratorType>
void iteratorTraitsTest(IteratorType it) {
    typename std::iterator_traits<IteratorType>::value_type temp;
    temp = *it;
    std::cout << temp << std::endl;
}

TEST(迭代器, 迭代器萃取) {
    std::vector v { 5 };
    iteratorTraitsTest(cbegin(v));
}

TEST(迭代器, 使用for循环和迭代器迭代vector中的元素) {
    std::vector values { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    for (auto iter { cbegin(values) }; iter != cend(values); ++iter) {
        std::cout << *iter << ' ';
    }
    std::cout << std::endl;
}

template <typename Iter>
void myPrint(Iter begin, Iter end) {
    for (auto iter { begin }; iter != end; ++iter) {
        std::cout << *iter << ' ';
    }
    std::cout << std::endl;
}

TEST(迭代器, myPrint函数测试) {
    std::vector values { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    myPrint(cbegin(values), cend(values));
}

template <typename Iter>
auto myFind(Iter begin, Iter end, typename std::iterator_traits<Iter>::value_type const &value) {
    for (auto iter { begin }; iter != end; ++iter) {
        if (*iter == value) {
            return iter;
        }
    }
    return end;
}

TEST(迭代器, myFind函数测试) {
    std::vector values { 11, 22, 33, 44 };
    auto result { myFind(cbegin(values), cend(values), 22) };
    if (result != cend(values)) {
        std::cout << std::format("Found value at position {}", distance(cbegin(values), result));
    }
    std::cout << std::endl;
}

/* -------------------------------------------------------------------------- */
/*                                    流迭代器                                    */
/* -------------------------------------------------------------------------- */

template <typename InputIter, typename OutputIter>
void myCopy(InputIter begin, InputIter end, OutputIter target) {
    for (auto iter { begin }; iter != end; ++iter, ++target) {
        *target = *iter;
    }
}

TEST(迭代器, 输出流迭代器) {
    std::vector myVector { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> vectorCopy(myVector.size());
    myCopy(cbegin(myVector), cend(myVector), begin(vectorCopy));

    myCopy(cbegin(myVector), cend(myVector), std::ostream_iterator<int> { std::cout, " " });
    std::cout << std::endl;
    myCopy(cbegin(vectorCopy), cend(vectorCopy), std::ostream_iterator<int> { std::cout, " " });
    std::cout << std::endl;
}

template <typename InputIter>
auto sum(InputIter begin, InputIter end) {
    auto sum { *begin };
    for (auto iter { ++begin }; iter != end; ++iter) {
        sum += *iter;
    }
    return sum;
}

TEST(迭代器, 输入流迭代器) {
    // std::istream_iterator<int> numbersIter { std::cin };
    // std::istream_iterator<int> endIter;
    // int result { sum(numbersIter, endIter) };
    // std::cout << "Sum: " << result << std::endl;
}

/* -------------------------------------------------------------------------- */
/*                                   迭代器适配器                                   */
/* -------------------------------------------------------------------------- */

TEST(迭代器, 插入迭代器) {
    std::vector vectorOne { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> vectorTwo;
    // std::back_insert_iterator<std::vector<int>> inserter { vectorTwo };
    // myCopy(cbegin(vectorOne), cend(vectorOne), inserter);
    // myCopy(cbegin(vectorOne), cend(vectorOne), std::back_inserter(vectorTwo));
    myCopy(cbegin(vectorOne), cend(vectorOne), std::back_insert_iterator { vectorTwo });
    std::cout << std::endl;
    myCopy(cbegin(vectorOne), cend(vectorOne), std::ostream_iterator<int> { std::cout, " " });
    std::cout << std::endl;

    std::vector vectorOne1 { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::set<int> setOne;

    // std::insert_iterator<std::set<int>> inserter { setOne, begin(setOne) };
    // myCopy(cbegin(vectorOne1), cend(vectorOne1), inserter);
    // myCopy(cbegin(vectorOne1), cend(vectorOne1), std::inserter(setOne, begin(setOne)));
    myCopy(cbegin(vectorOne1), cend(vectorOne1), std::insert_iterator { setOne, begin(setOne) });
    myCopy(cbegin(setOne), cend(setOne), std::ostream_iterator<int> { std::cout, " " });
    std::cout << std::endl;
}

TEST(迭代器, 逆向迭代器) {
    std::vector myVector { 11, 22, 33, 22, 11 };
    auto it1 { myFind(begin(myVector), end(myVector), 22) };
    auto it2 { myFind(rbegin(myVector), rend(myVector), 22) };

    if (it1 != end(myVector) && it2 != rend(myVector)) {
        std::cout << std::format("Found at position {} going forward.",
                                 std::distance(begin(myVector), it1))
                  << std::endl;
        std::cout << std::format("Found at position {} going backward.",
                                 std::distance(begin(myVector), --it2.base()))
                  << std::endl;
    } else {
        std::cout << "Failed to find." << std::endl;
    }
}

class MoveableClass {
public:
    MoveableClass() {
        std::cout << "Default construstor" << std::endl;
    }

    MoveableClass(MoveableClass const &src) {
        std::cout << "Copy constructor" << std::endl;
    }

    MoveableClass(MoveableClass &&src) noexcept {
        std::cout << "Move constructor" << std::endl;
    }

    MoveableClass &operator=(MoveableClass const &rhs) {
        std::cout << "Copy assignment operator" << std::endl;
        return *this;
    }

    MoveableClass &operator=(MoveableClass &&rhs) noexcept {
        std::cout << "Move assignment operator" << std::endl;
        return *this;
    }
};

TEST(迭代器, 移动迭代器) {
    std::vector<MoveableClass> vecSource;
    MoveableClass mc;
    vecSource.push_back(mc);
    vecSource.push_back(mc);

    std::vector<MoveableClass> vecOne { cbegin(vecSource), cend(vecSource) };
    // std::vector<MoveableClass> vecTwo { std::make_move_iterator(begin(vecSource)),
    //                                     std::make_move_iterator(end(vecSource)) };
    std::vector<MoveableClass> vecTwo { std::move_iterator(begin(vecSource)),
                                        std::move_iterator(end(vecSource)) };
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
