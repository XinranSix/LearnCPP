#include <bits/utility.h>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <tuple>

template <unsigned char f>
class Factorial {
public:
    static const unsigned long long value = (f * Factorial<f - 1>::value);
};

template <>
class Factorial<0> {
public:
    static const unsigned long long value { 1 };
};

// 立即函数实现阶乘
consteval unsigned long long factorial(unsigned char f) {
    if (f == 0) {
        return 1;
    }
    return f * factorial(f - 1);
}

TEST(模板元编程, 编译期阶乘) {
    std::cout << Factorial<6>::value << std::endl;
    std::cout << factorial(6) << std::endl;
}

template <int i>
struct Loop {
    template <typename FuncType>
    static inline void run(FuncType func) {
        Loop<i - 1>::run(func);
        func(i);
    }
};

template <>
struct Loop<0> {
    template <typename FunType>
    static inline void run(FunType /*func*/) {
        // func(0);
    }
};

void doWork(int i) {
    std::cout << "doWork(" << i << ")" << std::endl;
}

TEST(模板元编程, 循环展开) {
    Loop<3>::run(doWork);
}

template <typename TupleType, int n>
struct TuplePrint {
    TuplePrint(TupleType const &t) {
        TuplePrint<TupleType, n - 1> tp { t };
        std::cout << std::get<n - 1>(t) << std::endl;
    }
};

template <typename TupleType>
struct TuplePrint<TupleType, 0> {
    TuplePrint(TupleType const &) {}
};

// template <typename TupleType, int n>
// struct TuplePrintHelper {
//     TuplePrintHelper(TupleType const &t) {
//         TuplePrintHelper<TupleType, n - 1> tp { t };
//         std::cout << std::get<n - 1>(t) << std::endl;
//     }
// };

// template <typename TupleType>
// struct TuplePrintHelper<TupleType, 0> {
//     TuplePrintHelper(TupleType const &) {}
// };

// constexpr if 真™好用
template <typename TupleType, int n>
struct TuplePrintHelper {
    TuplePrintHelper(TupleType const &t) {
        if constexpr (n > 1) {
            TuplePrintHelper<TupleType, n - 1> tp { t };
        }
        std::cout << std::get<n - 1>(t) << std::endl;
    }
};

template <typename T>
void tuplePrint(T const &t) {
    TuplePrintHelper<T, std::tuple_size<T>::value> tph { t };
}

TEST(模板元编程, 打印tuple) {
    using MyTuple = std::tuple<int, std::string, bool>;
    MyTuple t1 { 16, "Test", true };
    TuplePrint<MyTuple, std::tuple_size<MyTuple>::value> tp { t1 };

    using namespace std;
    std::tuple t2 { 167, "Testing"s, false, 2.3 };
    tuplePrint(t2);
}

template <typename TupleType, int n = std::tuple_size<TupleType>::value>
void tuplePrint1(TupleType const &t) {
    if constexpr (n > 1) {
        tuplePrint1<TupleType, n - 1>(t);
    }
    std::cout << std::get<n - 1>(t) << std::endl;
}

TEST(模板元编程, constexpr_if) {
    using namespace std;
    std::tuple t1 { 167, "Testing"s, false, 2.3 };
    tuplePrint1(t1);
}

template <typename Tuple, size_t... Indices>
void tuplePrintHelper2(Tuple const &t, std::index_sequence<Indices...>) {
    ((std::cout << std::get<Indices>(t) << std::endl), ...);
}

template <typename... Args>
void tupePrint2(std::tuple<Args...> &t) {
    tuplePrintHelper2(t, std::index_sequence_for<Args...>());
} 

TEST(模板元编程, 使用编译期整数序列和折叠) {
    using namespace std;
    std::tuple t1 { 167, "Testing"s, false, 2, 3 };
    tupePrint2(t1);
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
