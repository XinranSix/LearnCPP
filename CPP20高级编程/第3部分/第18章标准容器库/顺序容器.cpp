#include <span>
#include <array>
#include <forward_list>
#include <list>
#include <cstddef>
#include <format>
#include <functional>
#include <iostream>
#include <gtest/gtest.h>
#include <iterator>
#include <limits>
#include <memory>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <deque>

/*
顺序容器包括：vector、deque、list、forward_list 和 list
*/

TEST(顺序容器, 固定长度vector) {
#if 0
    std::vector<double> doubleVector(10);

    double max { -std::numeric_limits<double>::infinity() };

    for (size_t i { 0 }; i < doubleVector.size(); ++i) {
        std::cout << std::format("Enter score {}: ", i + 1);
        std::cin >> doubleVector[i];
        if (doubleVector[i] > max) {
            max = doubleVector[i];
        }
    }

    max /= 100.0;
    for (auto &element : doubleVector) {
        element /= max;
        std::cout << element << " ";
    }
#endif
}

TEST(顺序容器, 动态长度的vector) {
#if 0
    std::vector<double> doubleVector;

    double max { -std::numeric_limits<double>::infinity() };

    for (size_t i { 1 }; true; ++i) {
        double temp;
        std::cout << std::format("Enter score {} (-1 to stop): ", i);
        std::cin >> temp;
        if (temp == -1) {
            break;
        }
        doubleVector.push_back(temp);
        if (temp > max) {
            max = temp;
        }
    }

    max /= 100.0;
    for (auto &element : doubleVector) {
        element /= max;
        std::cout << element << " ";
    }
#endif
}

class Element {
public:
    Element() {}
    virtual ~Element() = default;
};

TEST(顺序容器, vector之构造函数和析构函数) {
    std::vector<int> intVector1;
    std::vector<int> intVector2(10, 100);
    std::vector<std::string> stringVector(10, "hello");
    std::vector<Element> elementVector1;
    std::vector<int> intVector3({ 1, 2, 3, 4, 5, 6 });
    std::vector<int> intVector4 = { 1, 2, 3, 4, 5, 6 };
    std::vector<int> intVector6 { 1, 2, 3, 4, 5, 6 };
    std::vector intVector7 { 1, 2, 3, 4, 5, 6 };
    auto elementVector2 { std::make_unique<std::vector<Element>>(10) };
}

TEST(顺序容器, vector的复制和赋值) {
    std::vector<int> intVector1(10);
    intVector1.assign(5, 100);
    intVector1.assign({ 1, 2, 3, 4 });

    std::vector<int> vectorOne(10);
    std::vector<int> vectorTwo(5, 100);
    vectorOne.swap(vectorTwo);
}

TEST(顺序容器, vector的的比较) {
    std::vector<int> vectorOne(10);
    std::vector<int> vectorTwo(10);

    if (vectorOne == vectorTwo) {
        std::cout << "equal!" << std::endl;
    } else {
        std::cout << "not equal!" << std::endl;
    }

    vectorOne[3] = 50;

    if (vectorOne < vectorTwo) {
        std::cout << "vectorOne is less than vectorTwo" << std::endl;
    } else {
        std::cout << "vectorOne is not less than vectorTwo" << std::endl;
    }
}

TEST(顺序容器, vector迭代器) {
    std::vector<std::string> stringVector(10, "hello");

    // for (auto it { begin(stringVector) }; it != end(stringVector); ++it) {
    //     it->append(" there");
    // }

    for (auto &str : stringVector) {
        str.append(" there");
    }
}

TEST(顺序容器, vector迭代器之const_iterator) {}

TEST(顺序容器, vector迭代器之其他迭代器操作) {
    std::vector<int> intVector(10);
    auto it { begin(intVector) };
    it += 5;
    --it;
    *it = 4;
}

TEST(顺序容器, 在vector中存储引用) {
    std::string str1 { "Hello" };
    std::string str2 { "World" };

    std::vector<std::reference_wrapper<std::string>> vec { std::ref(str1) };
    vec.push_back(std::ref(str2));

    vec[1].get() += "!";

    std::cout << str1 << " " << str2 << std::endl;
}

template <typename T>
void printVector(std::vector<T> const &v) {
    for (auto &element : v) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

TEST(顺序容器, vector之添加和删除元素) {
    std::vector<int> vectorOne { 1, 2, 3, 5 };
    std::vector<int> vectorTwo;

    vectorOne.insert(cbegin(vectorOne) + 3, 4);

    for (int i { 6 }; i <= 10; ++i) {
        vectorTwo.push_back(i);
    }
    printVector(vectorOne);
    printVector(vectorTwo);

    vectorOne.insert(cend(vectorOne), cbegin(vectorTwo), cend(vectorTwo));
    printVector(vectorOne);

    vectorOne.erase(cbegin(vectorOne) + 1, cbegin(vectorOne) + 5);
    printVector(vectorOne);

    vectorTwo.clear();

    vectorTwo.insert(cbegin(vectorTwo), 10, 100);

    vectorTwo.pop_back();
    printVector(vectorTwo);

    std::vector values { 1, 2, 3, 2, 1, 2, 4, 5 };
    printVector(values);

    std::erase(values, 2);
    printVector(values);
}

TEST(顺序容器, vector之移动语义) {
    std::vector<std::string> vec;

    std::string myElement(5, 'a');
    // vec.push_back(myElement);
    vec.push_back(std::move(myElement));
    vec.push_back(std::string(5, 'a'));
}

TEST(顺序容器, vector之emplace) {
    std::vector<std::string> vec;

    vec.emplace_back(5, 'a');

    vec.emplace(begin(vec), 5, 'b');
    printVector(vec);
}

TEST(顺序容器, vector之内存分配方案) {
    std::vector<int> vec { 1, 2, 3 };

    std::cout << std::size(vec) << std::endl;
    std::cout << std::empty(vec) << std::endl;

    auto s1 { std::size(vec) };
    auto s2 { std::ssize(vec) }; // 非常鸡肋感觉
}

TEST(顺序容器, vector之内存回收) {
    std::vector<int> values;
    std::vector<int>().swap(values);
}

TEST(顺序容器, vector之直接访问数据) {
    std::vector<int> vec { 1, 2, 3 };
    int *data1 { vec.data() };
    int *data2 { std::data(vec) };
    // int *data3 { &vec[0] };// 对空的 vector 来说不安全，不要酱紫做
}

std::vector<int> createVectorOfSize(size_t size) {
    std::vector<int> vec(size);
    for (int contents { 0 }; auto &i : vec) {
        i = contents++;
    }
    return vec;
}

TEST(顺序容器, vector之移动语义1) {
    std::vector<int> myVector;
    myVector = createVectorOfSize(123);
    printVector(myVector);
}

/* -------------------------------------------------------------------------- */

template <typename T>
class RoundRobin {
public:
    explicit RoundRobin(size_t numExpected = 0);
    virtual ~RoundRobin() = default;

    RoundRobin(RoundRobin const &src) = delete;
    RoundRobin &operator=(RoundRobin const &rhs) = delete;

    RoundRobin(RoundRobin &&src) noexcept = default;
    RoundRobin &operator=(RoundRobin &&rhs) noexcept = default;

    void add(T const &element);

    void remove(T const &element);

    T &getNext();

private:
    std::vector<T> m_elements;
    typename std::vector<T>::iterator m_nextElement;
};

template <typename T>
RoundRobin<T>::RoundRobin(size_t numExpected) {
    m_elements.reserve(numExpected);
    m_nextElement = begin(m_elements);
}

template <typename T>
void RoundRobin<T>::add(T const &element) {
    std::ptrdiff_t pos { m_nextElement - begin(m_elements) };

    m_elements.push_back(element);
    m_nextElement = begin(m_elements) + pos;
}

template <typename T>
void RoundRobin<T>::remove(T const &element) {
    for (auto it { begin(m_elements) }; it != end(m_elements); ++it) {
        if (*it == element) {
            std::ptrdiff_t newPos;

            if (m_nextElement == end(m_elements) - 1 && m_nextElement == it) {
                // 如果是最后一个，将迭代器置于 0 的位置
                newPos = 0;
            } else if (m_nextElement <= it) {
                // 如果在要移除的元素之前
                newPos = m_nextElement - begin(m_elements);
            } else {
                // 如果在要移除的元素之后
                newPos = m_nextElement - begin(m_elements) - 1;
            }

            m_elements.erase(it);

            m_nextElement = begin(m_elements) + newPos;

            return;
        }
    }
}

template <typename T>
T &RoundRobin<T>::getNext() {
    if (m_elements.empty()) {
        throw std::out_of_range("No elements in the list");
    }

    auto &toReturn { *m_nextElement };

    ++m_nextElement;
    if (m_nextElement == end(m_elements)) {
        m_nextElement = begin(m_elements);
    }

    return toReturn;
}

class Process final {
public:
    explicit Process(std::string name) : m_name { std::move(name) } {}

    void doWorkDuringTimeSlice() {
        std::cout << "Process " << m_name << " performing work during time slice." << std::endl;
    }

    bool operator==(Process const &) const = default;

private:
    std::string m_name;
};

class Scheduler final {
public:
    explicit Scheduler(std::vector<Process> &processes) {
        for (auto &process : processes) {
            m_processes.add(process);
        }
    }

    void scheduleTimeSlice() {
        try {
            m_processes.getNext().doWorkDuringTimeSlice();
        } catch (Process const &process) {
            std::cout << "No more processes to schedule." << std::endl;
        }
    }

    void removeProcess(Process const &process) {
        m_processes.remove(process);
    }

private:
    RoundRobin<Process> m_processes;
};

TEST(顺序容器, vector示例_一个时间片轮转类) {
    std::vector processes { Process { "1" }, Process { "2" }, Process { "3" } };

    Scheduler scheduler { processes };
    for (int i { 0 }; i < 4; ++i) {
        scheduler.scheduleTimeSlice();
    }

    scheduler.removeProcess(processes[1]);
    std::cout << "Removed second process" << std::endl;

    for (int i { 0 }; i < 4; ++i) {
        scheduler.scheduleTimeSlice();
    }
}
/* -------------------------------------------------------------------------- */

TEST(顺序容器, vector_bool特化) {
    // 这东西不好，不要用
}

TEST(顺序容器, deque) {
    /*

    */
}

TEST(顺序容器, list串联操作) {

    std::list<std::string> dictionary { "aardvark", "ambulance" };
    std::list<std::string> bWords { "bathos", "balderdash" };

    dictionary.push_back("canticle");
    dictionary.push_back("consumerism");

    if (!bWords.empty()) {
        auto iterLastB { --(cend(bWords)) };
        auto it { cbegin(dictionary) };
        for (; it != cend(dictionary); ++it) {
            if (*it > *iterLastB) {
                break;
            }
            dictionary.splice(it, bWords);
        }
    }

    for (auto const &word : dictionary) {
        std::cout << word << std::endl;
    }
}

std::list<std::string> getTotalEnrollment(std::vector<std::list<std::string>> const &courseStudents,
                                          std::list<std::string> const &droppedStudents) {
    std::list<std::string> allStudents;

    for (auto &lst : courseStudents) {
        allStudents.insert(cend(allStudents), cbegin(lst), cend(lst));
    }

    allStudents.sort();

    allStudents.unique();

    for (auto &str : droppedStudents) {
        allStudents.remove(str);
    }

    return allStudents;
}

TEST(顺序容器, list案例_确定注册情况) {}

TEST(顺序容器, forward_list) {
    std::forward_list<int> list1 { 5, 6 };
    std::forward_list<int> list2 { 1, 2, 3, 4 };
    std::forward_list<int> list3 { 7, 8, 9 };

    list1.splice_after(list1.before_begin(), list2);
    list1.push_front(0);

    auto iter { list1.before_begin() };
    auto iterTemp { iter };
    while (++iterTemp != end(list1)) {
        ++iter;
    }
    list1.insert_after(iter, cbegin(list3), cend(list3));
    for (auto &i : list1) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

TEST(顺序容器, array) {
    std::array<int, 3> arr { 9, 8, 7 };

    std::cout << "Array size = " << arr.size() << std::endl;

    for (auto const &i : arr) {
        std::cout << i << std::endl;
    }

    std::cout << "Performing arr.fill(3)..." << std::endl;

    arr.fill(3);

    for (auto iter { cbegin(arr) }; iter != cend(arr); ++iter) {
        std::cout << *iter << std::endl;
    }

    std::array<int, 3> myArray { 11, 22, 33 };
    std::cout << std::get<1>(myArray) << std::endl;
    // std::cout << std::get<10>(myArray) << std::endl;

    auto arr1 { std::to_array({ 11, 22, 33 }) };
    double carray[] { 9, 8, 7, 6 };
    auto arr2 { std::to_array(carray) };
}

void print(std::span<const int> values) {
    for (auto const &value : values) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

TEST(顺序容器, span) {
    std::vector v { 11, 22, 33, 44, 55, 66 };
    print(v);

    std::span mySpan { v };
    print(mySpan);

    std::span subspan { mySpan.subspan(2, 3) };
    print(subspan);

    print({ v.data() + 2, 3 });

    std::array<int, 5> arr { 5, 4, 3, 2, 1 };
    print(arr);
    print({ arr.data() + 2, 3 });

    int carr[] { 9, 8, 7, 6, 5 };
    print(carr);
    print({ carr + 2, 3 });
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
