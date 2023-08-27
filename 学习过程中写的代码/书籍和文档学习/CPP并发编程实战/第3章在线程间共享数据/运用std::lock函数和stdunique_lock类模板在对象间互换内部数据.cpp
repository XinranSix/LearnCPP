#include <iostream>
#include <mutex>

class some_big_object {};

void swap(some_big_object &, some_big_object &) {}

class X {
public:
    X(some_big_object const &sd) : some_detail { sd } {}

    friend void swap(X &lhs, X &rhs) {
        if (&lhs == &rhs) {
            return;
        }
        std::unique_lock<std::mutex> lock_a { lhs.m, std::defer_lock };
        std::unique_lock<std::mutex> lock_b { rhs.m, std::defer_lock };
        std::lock(lock_a, lock_b);
        swap(lhs.some_detail, rhs.some_detail);
    }

private:
    some_big_object some_detail;
    std::mutex m;
};

int main(int argc, char *argv[]) {
    return 0;
}
