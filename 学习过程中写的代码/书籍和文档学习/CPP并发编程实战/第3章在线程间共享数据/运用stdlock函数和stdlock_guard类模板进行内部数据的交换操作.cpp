#include <iostream>
#include <mutex>

class some_big_object {};

void swap(some_big_object &lhs, some_big_object &rhs) {}

class X {
public:
    X(some_big_object const &sd) : some_detail { sd } {}

    friend void swap(X &lhs, X &rhs) {
        if (&lhs == &rhs) {
            return;
        }
        // std::lock 函数会保证 all-or-nothing
        // 如果发生错误或异常，会自动释放以加锁的 mutex 上的锁
        std::lock(lhs.m, rhs.m); // 对两个 mutex 进行加锁
        // NOTE: std::adopt_lock 的意思是前面的 mutex
        // 以加锁，不要在构造函数里在加锁，而只是接受其所有权
        std::lock_guard<std::mutex> lock_a { lhs.m, std::adopt_lock };
        std::lock_guard<std::mutex> lock_b { rhs.m, std::adopt_lock };

        /*
        // 此处代码和上面等价
        // std::scoped_lock 是 C++ 17 引入的std::scoped_lock
                std::scoped_lock guard{lhs.m,rhs.m};
        */

        swap(lhs.some_detail, rhs.some_detail);
    }

private:
    some_big_object some_detail;
    std::mutex m;
};

int main(int argc, char *argv[]) {
    return 0;
}
