#include <algorithm>
#include <csignal>
#include <iostream>
#include <gtest/gtest.h>
#include <numeric>
#include <utility>
#include <vector>
#include "boost/signals2.hpp"
#include "boost/signals2/detail/slot_groups.hpp"

void slots1() { std::cout << "slot1 called" << std::endl; }
void slots2() { std::cout << "slot2 called" << std::endl; }

TEST(signals2, 基本用法) {
    boost::signals2::signal<void()> sig;

    sig.connect(&slots1);
    // sig.connect(&slots2);
    sig.connect(&slots2, boost::signals2::at_front);
    sig();
}

template <int N>
struct slots {
    void operator()() { std::cout << "slot" << N << " called" << std::endl; }
};

TEST(signals2, 使用组号) {
    boost::signals2::signal<void()> sig;

    sig.connect(slots<1> {}, boost::signals2::at_back);
    sig.connect(slots<100> {}, boost::signals2::at_front);

    sig.connect(5, slots<51> {}, boost::signals2::at_back);
    sig.connect(5, slots<55> {}, boost::signals2::at_front);

    sig.connect(3, slots<30> {}, boost::signals2::at_front);
    sig.connect(3, slots<33> {}, boost::signals2::at_back);

    sig.connect(10, slots<10> {});

    sig();
}

template <int N>
struct slots10 {
    int operator()(int x) {
        std::cout << "slot" << N << " called" << std::endl;
        return x * N;
    }
};

TEST(signals2, 返回值) {
    boost::signals2::signal<int(int)> sig;

    sig.connect(slots10<10> {});
    sig.connect(slots10<20> {});
    sig.connect(slots10<50> {});

    std::cout << *sig(2) << std::endl;
}

template <typename T>
class combiner {
    T v {};

public:
    using result_type = std::pair<T, T>;

    combiner(T t = T {}) : v { t } {}

    template <typename InputIterator>
    result_type operator()(InputIterator begin, InputIterator end) const {
        if (begin == end) {
            return result_type {};
        }

        std::vector<T> vec(begin, end);

        T sum = std::accumulate(vec.begin(), vec.end(), v);
        T max = *std::max_element(vec.begin(), vec.end());

        return result_type(sum, max);
    }
};

TEST(signals2, 合并器) {
    boost::signals2::signal<int(int), combiner<int>> sig;

    sig.connect(slots10<10> {});
    sig.connect(slots10<20> {});
    sig.connect(slots10<30> {}, boost::signals2::at_front);

    auto x { sig(2) };
    std::cout << x.first << ", " << x.second << std::endl;
}


TEST(signals2, 管理信号连接) {
    
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
