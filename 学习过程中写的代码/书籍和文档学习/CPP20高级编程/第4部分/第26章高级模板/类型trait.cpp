#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <type_traits>

template <typename T>
void processHelper(T const &t, std::true_type) {
    std::cout << t << " is an integral type." << std::endl;
}

template <typename T>
void processHelper(T const &t, std::false_type) {
    std::cout << t << " is a non-integral type." << std::endl;
}

template <typename T>
void process1(T const &t) {
    processHelper(t, typename std::is_integral<T>::type {});
}

template <typename T>
void process2(T const &t) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << t << " is an integral type." << std::endl;
    } else {
        std::cout << t << " is an non-integral type." << std::endl;
    }
}

TEST(类型trait, 使用类型类别) {
    if (std::is_integral<int>::value) {
        std::cout << "int is integral" << std::endl;
    } else {
        std::cout << "int is not integral" << std::endl;
    }

    if (std::is_class<std::string>::value) {
        std::cout << "string is a class" << std::endl;
    } else {
        std::cout << "string is not a class" << std::endl;
    }

    std::cout << std::endl;
    using namespace std;
    process1(123);
    process1(2.2);
    process1("Test"s);

    std::cout << std::endl;
    process2(123);
    process2(2.2);
    process2("Test"s);
}

template <typename T1, typename T2>
void same(T1 const &t1, T2 const &t2) {
    bool areTypesTheSame { std::is_same_v<T1, T2> };
    std::cout << std::format("'{}' and '{}' are {} types.", t1, t2,
                             (areTypesTheSame ? "the same" : "different"))
              << std::endl;
}

TEST(类型trait, 使用类型关系) {
    same(1, 32);
    same(1, 3.01);
    using namespace std;
    same(3.01, "Test"s);
}

// std::conditional<bool Cond, typename Iftrue, typename Iffalse>

template <typename T>
constexpr std::conditional_t<std::is_nothrow_move_assignable_v<T>, T &&, const T &>
move_assign_if_noexcept(T &t) noexcept {
    return std::move(t);
}

struct MoveAssignable {
    MoveAssignable &operator=(MoveAssignable const &) {
        std::cout << "copy assign" << std::endl;
        return *this;
    }
    MoveAssignable &operator=(MoveAssignable &&) {
        std::cout << "move assign" << std::endl;
        return *this;
    }
};

struct MoveAssignableNoexcept {
    MoveAssignableNoexcept &operator=(MoveAssignableNoexcept const &) {
        std::cout << "copy assign" << std::endl;
        return *this;
    }
    MoveAssignableNoexcept &operator=(MoveAssignableNoexcept &&) noexcept {
        std::cout << "move assign" << std::endl;
        return *this;
    }
};

TEST(类型trait, 使用条件类型trait) {
    MoveAssignable a, b;
    a = move_assign_if_noexcept(b);
    MoveAssignableNoexcept c, d;
    c = move_assign_if_noexcept(d);
}

template <typename T1, typename T2>
std::enable_if_t<std::is_same_v<T1, T2>, bool> checkType(T1 const &t1, T2 const &t2) {
    std::cout << std::format("'{}' and '{}' are the same types.", t1, t2) << std::endl;
    return true;
}

template <typename T1, typename T2>
std::enable_if_t<!std::is_same_v<T1, T2>, bool> checkType(T1 const &t1, T2 const &t2) {
    std::cout << std::format("'{}' and '{}' are different types.", t1, t2) << std::endl;
    return false;
}

TEST(类型trait, 使用enable_if) {
    checkType(1, 32);
    checkType(1, 3.01);
    using namespace std;
    checkType(3.01, "Test"s);
}

struct IsDoable {
    void doit() const {
        std::cout << "IsDoable::doit()" << std::endl;
    }
};

class Derived : public IsDoable {};

/*
template <typename T>
std::enable_if_t<std::is_base_of_v<IsDoable, T>, void> callDoit(T const &t) {
    t.doit();
}

template <typename T>
std::enable_if_t<!std::is_base_of_v<IsDoable, T>, void> callDoit(T const &t) {
    std::cout << "Cannot call doit()!" << std::endl;
}
*/

/*
template <typename T>
void callDoit([[maybe_unused]] const T &t) {
    if constexpr (std::is_base_of_v<IsDoable, T>) {
        t.doit();
    } else {
        std::cout << "Cannot call doit()!" << std::endl;
    }
}
*/

template <typename T>
void callDoit([[maybe_unused]] const T &t) {
    if constexpr (std::is_invocable_v<decltype(&IsDoable::doit), T>) {
        t.doit();
    } else {
        std::cout << "Cannot call doit()!" << std::endl;
    }
}

TEST(类型trait, 使用constexpr_if简化enable_if) {
    Derived d;
    callDoit(d);
    callDoit(123);
}

TEST(类型trait, 逻辑运算trait) {
    std::cout << std::conjunction_v<std::is_integral<int>, std::is_integral<short>> << " ";
    std::cout << std::conjunction_v<std::is_integral<int>, std::is_integral<double>> << " ";
    std::cout << std::disjunction_v<std::is_integral<int>, std::is_integral<double>,
                                    std::is_integral<short>> << " ";

    std::cout << std::negation_v<std::is_integral<int>> << std::endl;
}

template <typename T>
void foo(T const &t) {
    static_assert(std::is_integral_v<T>, "T should be an integral type.");
}

TEST(类型trait, 静态断言) {
    static_assert(sizeof(void *), "Requires 64-bit compilation.");
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
