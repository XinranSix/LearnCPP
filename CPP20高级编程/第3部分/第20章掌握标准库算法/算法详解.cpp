#include <execution>
#include "yj/tools/output_container.h"
#include <algorithm>
#include <ctime>
#include <format>
#include <functional>
#include <iostream>
#include <gtest/gtest.h>
#include <list>
#include <map>
#include <random>
#include <string>
#include <string_view>
#include <vector>
#include <numeric>

TEST(算法详解, 非修改序列算法之搜索算法) {
    std::vector myVector { 5, 6, 9, 8, 8, 3 };
    auto beginIter { cbegin(myVector) };
    auto endIter { cend(myVector) };

    auto it { std::find_if_not(beginIter, endIter, [](int i) { return i < 8; }) };
    if (it != endIter) {
        std::cout << "First element not < 8 is " << *it << std::endl;
    }

    it = std::adjacent_find(beginIter, endIter);
    if (it != endIter) {
        std::cout << "Found two consecutive equal elements with value " << *it << std::endl;
    }

    std::vector targets { 8, 9 };
    it = std::find_first_of(beginIter, endIter, cbegin(targets), cend(targets));
    if (it != endIter) {
        std::cout << "Found one of 8 or 9: " << *it << std::endl;
    }

    std::vector sub { 8, 3 };
    it = std::search(beginIter, endIter, cbegin(sub), cend(sub));
    if (it != endIter) {
        std::cout << "Found subsequence {8, 3}" << std::endl;
    } else {
        std::cout << "Unable to find subsequence {8, 3}" << std::endl;
    }

    auto it2 { std::find_end(beginIter, endIter, cbegin(sub), cend(sub)) };
    if (it != it2) {
        std::cout << "Error: search and find_end found different subsequences "
                  << "even though there is only one match." << std::endl;
    }

    it = std::search_n(beginIter, endIter, 2, 8);
    if (it != endIter) {
        std::cout << "Found two consecutive 8s" << std::endl;
    } else {
        std::cout << "Unable to find two consecutive 8s" << std::endl;
    }
}

TEST(算法详解, 非修改序列算法之专用搜索算法) {
    std::string text { "This is the haystack to search a needle in." };
    std::string toSearchFor { "needle" };

    std::boyer_moore_searcher searcher { cbegin(toSearchFor), cend(toSearchFor) };
    auto result { std::search(cbegin(text), cend(text), searcher) };
    if (result != cend(text)) {
        std::cout << "Found the needle." << std::endl;
    } else {
        std::cout << "Needle not found." << std::endl;
    }
}

template <typename Container>
void populate(Container &cont) {
    while (true) {
        std::cout << "Enter a number (0 to quit): ";
        int value {};
        std::cin >> value;
        if (value == 0) {
            break;
        }
        cont.push_back(value);
    }
}

TEST(算法详解, 非修改序列算法之比较算法) {
    /*
    std::equal(): 如果所有对应元素都相等，则返回 true
    std::mismathch():
    std::lexicographical_compare()
    std::lexicographical_compare_three_way()
    */

#if 0
    std::vector<int> myVector;
    std::list<int> myList;

    std::cout << "Populate the vector:" << std::endl;
    populate(myVector);
    std::cout << "Populate the list:" << std::endl;
    populate(myList);

    if (std::equal(cbegin(myVector), cend(myVector), cbegin(myList), cend(myList))) {
        std::cout << "The two containers have equal elements" << std::endl;
    } else {
        auto miss { std::mismatch(cbegin(myVector), cend(myVector), cbegin(myList), cend(myList)) };
    }

    if (std::lexicographical_compare(cbegin(myVector), cend(myVector), cbegin(myList),
                                     cend(myList))) {
        std::cout << "The vector is lexicographcally first." << std::endl;
    } else {
        std::cout << "The list is lexicographcally first." << std::endl;
    }
#endif
}

TEST(算法详解, 非修改序列算法之计数算法) {
    /*
    all_of
    any_of
    none_of
    count
    count_if
    */

    std::vector vec2 { 1, 1, 1, 1 };
    if (std::all_of(cbegin(vec2), cend(vec2), [](int i) { return i == 1; })) {
        std::cout << "All elements are == 1" << std::endl;
    } else {
        std::cout << "Not all elements are == 1" << std::endl;
    }

    std::vector vec3 { 0, 0, 1, 0 };
    if (std::any_of(cbegin(vec3), cend(vec3), [](int i) { return i == 1; })) {
        std::cout << "At least one element == 1" << std::endl;
    } else {
        std::cout << "No elements are == 1" << std::endl;
    }

    std::vector vec4 { 0, 0, 0, 0 };
    if (std::none_of(cbegin(vec4), cend(vec4), [](int i) { return i == 1; })) {
        std::cout << "All elements are != 1" << std::endl;
    } else {
        std::cout << "Some elements are == 1" << std::endl;
    }

    std::vector values { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int value { 3 };
    auto tally { std::count_if(cbegin(values), cend(values),
                               [value](int i) { return i > value; }) };
    std::cout << std::format("Found {} values > {}.", tally, value) << std::endl;
}

TEST(算法详解, 修改序列算法之生成_generate) {
    std::vector<int> vec(10);
    int value { 1 };
    std::generate(begin(vec), end(vec), [&value] {
        value *= 2;
        return value;
    });
    for (auto const &i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

template <typename Container>
void populateContainer(Container &cont) {
    while (true) {
        std::cout << "Enter a number (0 to quit): ";
        int value;
        std::cin >> value;
        if (value == 0) {
            break;
        }
        cont.push_back(value);
    }
}

TEST(算法详解, 修改序列算法之转换_tranform) {
// 我喜欢叫他变换
#if 0
    std::vector<int> myVector;
    populateContainer(myVector);

    std::cout << "The vector contains: " << std::endl;
    for (auto const &i : myVector) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::transform(begin(myVector), end(myVector), begin(myVector), [](int i) { return i + 100; });

    std::cout << "The value contains: " << std::endl;
    for (auto const &i : myVector) {
        std::cout << i << " ";
    }
#endif

#if 0
    std::vector<int> vec1, vec2;
    std::cout << "Vector1:" << std::endl;
    populateContainer(vec1);
    std::cout << "Vector2:" << std::endl;
    populateContainer(vec2);

    if (vec2.size() < vec1.size()) {
        std::cout << "Vector2 should be at least the same size as vector1." << std::endl;
    } else {
        auto printContainer { [](auto const &container) {
            for (auto &i : container) {
                std::cout << i << ' ';
            }
            std::cout << std::endl;
        } };

        std::cout << "Vector1: ";
        printContainer(vec1);
        std::cout << "Vector2: ";
        printContainer(vec2);

        std::transform(begin(vec1), end(vec1), begin(vec2), end(vec2),
                       [](int a, int b) { return a + b; });
    }

#endif
}

TEST(算法详解, 修改序列算法之拷贝_copy) {
#if 0
    std::vector<int> vec1, vec2;
    populateContainer(vec1);
    vec2.resize(vec1.size());
    // std::copy(cbegin(vec1), cend(vec1), begin(vec2));
    std::copy_backward(cbegin(vec1), cend(vec1), end(vec2));
    for (auto const &i : vec2) {
        std::cout << i << " ";
    }
#endif
}

TEST(算法详解, 修改序列算法之拷贝_copy_if) {
#if 0
    std::vector<int> vec1, vec2;
    populateContainer(vec1);
    vec2.resize(std::size(vec1));
    auto endIterator { std::copy_if(cbegin(vec1), cend(vec1), begin(vec2),
                                    [](int i) { return i % 2 == 0; }) };
    vec2.erase(endIterator, end(vec2));
    for (auto const &i : vec2) {
        std::cout << i << " ";
    }
#endif
}

TEST(算法详解, 修改序列算法之拷贝_copy_n) {
#if 0
    std::vector<int> vec1, vec2;
    populateContainer(vec1);
    size_t tally { 0 };
    std::cout << "Enter number of elements you want to copy: " << std::endl;
    std::cin >> tally;
    tally = std::min(tally, std::size(vec1));
    vec2.resize(tally);
    std::copy_n(cbegin(vec1), tally, begin(vec2));
    for (auto const &i : vec2) {
        std::cout << i << " ";
    }
#endif
}

class MyClass {
public:
    MyClass() = default;
    MyClass(MyClass const &src) = default;
    MyClass(std::string str) : m_str { std::move(str) } {}
    virtual ~MyClass() = default;

    MyClass &operator=(MyClass &&rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        m_str = std::move(rhs.m_str);
        std::cout << std::format("Move operator= (m_str={})", m_str) << std::endl;
        return *this;
    }

    void setString(std::string str) {
        m_str = std::move(str);
    }

    std::string const &getString() const {
        return m_str;
    }

private:
    std::string m_str;
};

TEST(算法详解, 修改序列算法之移动_move) {
    std::vector<MyClass> vecSrc { MyClass { "a" }, MyClass { "b" }, MyClass { "c" } };
    std::vector<MyClass> vecDst { vecSrc.size() };
    std::move(begin(vecSrc), end(vecSrc), begin(vecDst));
    for (auto const &c : vecDst) {
        std::cout << c.getString() << " ";
    }
    std::cout << std::endl;
}

TEST(算法详解, 修改序列算法之移动_move_backward) {}

TEST(算法详解, 修改序列算法之替换replace和replace_if) {
#if 0
    std::vector<int> vec;
    populateContainer(vec);
    std::replace_if(
        begin(vec), end(vec), [](int i) { return i % 2 != 0; }, 0);
    for (auto const &i : vec) {
        std::cout << i << " ";
    }
#endif
}

void removeEmptyStrings(std::vector<std::string> &strings) {
    std::erase_if(strings, [](std::string const &str) { return str.empty(); });
}

// 如果还未支持 C++ 20 的 erase 算法，可以使用如下技巧
void removeEmptyStrings1(std::vector<std::string> &strings) {
    auto it { std::remove_if(begin(strings), end(strings),
                             [](std::string const &str) { return str.empty(); }) };
    strings.erase(it, end(strings));
}

TEST(算法详解, 修改序列算法之擦除erase和erase_if) {
    std::vector<std::string> myVector { "", "One", "two", "three", "four" };
    std::cout << myVector << std::endl;
    removeEmptyStrings(myVector);
    std::cout << myVector << std::endl;
}

TEST(算法详解, 修改序列算法之唯一化unique) {}

TEST(算法详解, 修改序列算法之乱序shuffle) {
    // 洗牌算法
    std::vector values { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::random_device seeder;
    const auto seed { seeder.entropy() ? seeder() : std::time(nullptr) };
    std::default_random_engine engine { static_cast<std::default_random_engine::result_type>(
        seed) };

    for (int i { 0 }; i < 6; ++i) {
        std::shuffle(begin(values), end(values), engine);
        for (auto const &value : values) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

TEST(算法详解, 修改序列算法之抽样sample) {
    // 采样
    std::vector values { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const size_t numberOfSamples { 5 };
    std::vector<int> samples { numberOfSamples };

    std::random_device seeder;
    const auto seed { seeder.entropy() ? seeder() : time(nullptr) };
    std::default_random_engine engine(static_cast<std::default_random_engine::result_type>(seed));

    for (int i { 0 }; i < 6; ++i) {
        std::sample(cbegin(values), cend(values), begin(samples), numberOfSamples, engine);
        for (auto const &sample : samples) {
            std::cout << sample << " ";
        }
        std::cout << std::endl;
    }
}

TEST(算法详解, 修改序列算法之反转reverse) {
#if 0
    std::vector<int> values;
    populateContainer(values);
    std::reverse(begin(values), end(values));
    for (auto const &i : values) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
#endif
}

TEST(算法详解, 修改序列算法之移动元素reverse) {
    std::vector values { 11, 22, 33, 44, 55 };
    for (auto const &value : values) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    auto newEnd { std::shift_left(begin(values), end(values), 2) };
    values.erase(newEnd, end(values));
    for (auto const &value : values) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    auto newBegin { std::shift_right(begin(values), end(values), 2) };
    values.erase(begin(values), newBegin);
    for (auto const &value : values) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

class SumAndProduct {
public:
    void operator()(int value) {
        m_sum += value;
        m_product *= value;
    }
    int getSum() const {
        return m_sum;
    }

    int getProduct() const {
        return m_product;
    };

private:
    int m_product { 1 };
    int m_sum { 0 };
};

TEST(算法详解, 操作算法之for_each) {
    std::map<int, int> myMap { { 4, 40 }, { 5, 50 }, { 6, 60 } };
    std::for_each(cbegin(myMap), cend(myMap),
                  [](auto const &p) { std::cout << p.first << "->" << p.second << std::endl; });

#if 0
    std::vector<int> myVector;
    populateContainer(myVector);
#endif

#if 0
    int sum { 0 };
    int product { 1 };
    std::for_each(cbegin(myVector), cend(myVector), [&sum, &product](int i) {
        sum += i;
        product *= i;
    });
#endif

#if 0
    SumAndProduct calculator;
    calculator = std::for_each(cbegin(myVector), cend(myVector), calculator);
    std::cout << "The sum is " << calculator.getSum() << std::endl;
    std::cout << "The product is " << calculator.getProduct() << std::endl;
#endif
}

TEST(算法详解, 操作算法之for_each_n) {
    std::map<int, int> myMap { { 4, 40 }, { 5, 50 }, { 6, 60 } };
    std::for_each_n(cbegin(myMap), 2,
                    [](auto const &p) { std::cout << p.first << "->" << p.second << std::endl; });
}

TEST(算法详解, 分区算法之partition_copy) {
#if 0
    std::vector<int> vec1, vecOdd, vecEven;
    populateContainer(vec1);
    vecOdd.resize(std::size(vec1));
    vecEven.resize(std::size(vec1));

    auto pairIters { std::partition_copy(cbegin(vec1), cend(vec1), begin(vecEven), end(vecEven),
                                         [](int i) { return i % 2 == 0; }) };

    vecEven.erase(pairIters.first, end(vecEven));
    vecOdd.erase(pairIters.second, end(vecOdd));

    std::cout << "Even number: ";
    for (auto const &i : vecEven) {
        std::cout << i << " ";
    }
    std::cout << std::endl << "Odd number: ";
    for (auto const &i : vecOdd) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
#endif
}

TEST(算法详解, 分区算法之partition) {
#if 0
    std::vector<int> values;
    populateContainer(values);

    auto pairIters { std::partition(begin(values), end(values), [](int i) { return i % 2 == 0; }) };

    std::cout << "Partitoned result: ";
    for (auto const &i : values) {
        std::cout << i << std::endl;
    } 
    std::cout << std::endl;

#endif
}

TEST(算法详解, 排序算法) {
#if 0
    std::vector<int> values;
    populateContainer(values);
    std::sort(begin(values), end(values), std::greater<> {});
#endif

#if 0
    std::vector<int> values;
    populateContainer(values);
    std::nth_element(begin(values), end(values) + 2, end(values), std::greater<> {});
    std::cout << "3rd largest value: " << values[2] << std::endl;
#endif

#if 0
    std::vector<int> values;
    populateContainer(values);
    std::nth_element(begin(values), end(values) + 4, end(values), std::greater<> {});
    std::sort(begin(values), end(values));
    std::for_each_n(begin(values), 5, [](auto const &element) { std::cout << element << " "; });
#endif
}

TEST(算法详解, 二分查找算法) {
    /*
    binary_search()
    lower_bound()
    upper_bound()
    equal_range()
    */
#if 0
    std::vector<int> values;
    populateContainer(values);

    std::sort(begin(values), end(values));

    std::cout << "Sorted vector: ";
    for (auto const &i : values) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    while (true) {
        int number {};
        std::cout << "Enter a number to insert (o to quit): ";
        std::cin >> number;
        if (number == 0) {
            break;
        }

        auto iter { std::lower_bound(begin(values), end(values), number) };
        values.insert(iter, number);

        std::cout << "New vector: ";
        for (auto const &i : values) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
#endif

#if 0
    std::vector<int> values;
    populateContainer(values);

    std::sort(begin(values), end(values));

    while (true) {
        int number {};
        std::cout << "Enter a number to find (0 to quit): ";
        std::cin >> number;
        if (number == 0) {
            break;
        }

        if (std::binary_search(cbegin(values), cend(values), number)) {
            std::cout << "That number is in the vector." << std::endl;
        } else {
            std::cout << "That number is not the vectir." << std::endl;
        }
    }
#endif
}

template <typename Iterator>
void DumpRange(std::string_view message, Iterator begin, Iterator end) {
    std::cout << message;
    std::for_each(begin, end, [](auto const &element) { std::cout << element << " "; });
    std::cout << std::endl;
}

TEST(算法详解, 集合算法) {
#if 0
    std::vector<int> vec1, vec2, result;
    std::cout << "Enter elements for set1: " << std::endl;
    populateContainer(vec1);
    std::cout << "Enter elements for set2: " << std::endl;
    populateContainer(vec2);

    std::sort(begin(vec1), end(vec1));
    std::sort(begin(vec2), end(vec2));

    if (std::includes(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2))) {
        std::cout << "The second set is a subset of list the first." << std::endl;
    }

    if (std::includes(cbegin(vec2), cend(vec2), cbegin(vec1), cend(vec1))) {
        std::cout << "The second set is a subset of list the first." << std::endl;
    }

    result.resize(std::size(vec1) + std::size(vec2));
    auto newEnd { std::set_union(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2),
                                 begin(result)) };
    DumpRange("The union is: ", begin(result), newEnd);

    newEnd =
        std::set_intersection(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2), begin(result));
    DumpRange("The intersection is: ", begin(result), newEnd);

    newEnd = std::set_difference(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2), begin(result));
    DumpRange("The difference between set 1 and 2 is: ", begin(result), newEnd);

    newEnd = std::set_symmetric_difference(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2),
                                           begin(result));
    DumpRange("The symmetric difference between set 1 and 2 is: ", begin(result), newEnd);
#endif
}

TEST(算法详解, 集合算法_merge) {
#if 0
    // 有序归并
    std::vector<int> vectorOne, vectorTwo, vectorMerged;
    std::cout << "Enter values for first vector: " << std::endl;
    populateContainer(vectorOne);
    std::cout << "Enter values for second vector: " << std::endl;
    populateContainer(vectorTwo);

    std::sort(begin(vectorOne), end(vectorOne));
    std::sort(begin(vectorTwo), end(vectorTwo));

    vectorMerged.resize(std::size(vectorOne) + std::size(vectorTwo));

    std::merge(cbegin(vectorOne), cend(vectorOne), cbegin(vectorTwo), cend(vectorTwo),
               begin(vectorMerged));

    DumpRange("Merged vector: ", cbegin(vectorMerged), cend(vectorMerged));
#endif
}

TEST(算法详解, 最大最小算法) {
    // min max minmax
    // min_element max_element minmax_element
    int x { 4 }, y { 5 };
    std::cout << std::format("x is {} and y is {}", x, y) << std::endl;
    std::cout << "Max is " << std::max(x, y) << std::endl;
    std::cout << "Min is " << std::min(x, y) << std::endl;

    int x1 { 2 }, x2 { 9 }, x3 { 3 }, x4 { 12 };
    std::cout << "Max of 4 elements is " << std::max({ x1, x2, x3, x4 }) << std::endl;
    std::cout << "Min of 4 elements is " << std::min({ x1, x2, x3, x4 }) << std::endl;

    auto p2 { std::minmax({ x1, x2, x3, x4 }) };
    std::cout << std::format("Minmax of 4 elemets is <{}, {}>", p2.first, p2.second) << std::endl;

    auto [min1, max1] { std::minmax({ x1, x2, x3, x4 }) };
    std::cout << std::format("Minmax of 4 elemets is <{}, {}>", min1, max1) << std::endl;

    std::vector values { 11, 33, 22 };
    auto [min2, max2] { std::minmax_element(cbegin(values), cend(values)) };
    std::cout << std::format("minmax_element() result: <{}, {}>", *min2, *max2) << std::endl;
}

TEST(算法详解, clamp) {
    std::cout << std::clamp(-3, 1, 10) << std::endl;
    std::cout << std::clamp(3, 1, 10) << std::endl;
    std::cout << std::clamp(22, 1, 10) << std::endl;
}

/* -------------------------------------------------------------------------- */

TEST(算法详解, 并行算法) {
    std::vector<int> myVector;
    std::sort(std::execution::par, begin(myVector), end(myVector));
}

TEST(算法详解, 约束算法) {
    std::vector values { 1, 2, 3 };
    // auto result { std::ranges::find(cbegin(values), cend(values), 2) };
    auto result { std::ranges::find(values, 2) };
    if (result != cend(values)) {
        std::cout << *result << std::endl;
    }
}

/* -------------------------------------------------------------------------- */

TEST(算法详解, 数值处理算法之iota) {
    std::vector<int> values(10);
    std::iota(begin(values), end(values), 5);
    for (auto &i : values) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

TEST(算法详解, 数值处理算法之reduce) {
    std::vector<int> v1 { 1, 2, 3, 4 };
    std::vector<int> v2 { 9, 8, 7, 6 };
    std::cout << std::inner_product(cbegin(v1), cend(v1), cbegin(v2), 0) << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
