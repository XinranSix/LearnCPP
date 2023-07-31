#include <utility>
#include <iostream>
#include <thread>

class X {
private:
    int *data;

public:
    X() : data(new int[1000000]) {}

    ~X() { delete[] data; }
    X(const X &other) : data(new int[1000000]) {
        std::copy(other.data, other.data + 1000000, data);
    }

    X(X &&other) : data(other.data) {
        std::cout << "移动构造函数" << std::endl;

        other.data = nullptr;
    }
};

void do_stuff(X &&x_) {
    X a(x_);
    X b(std::move(x_));
}

int main(int arvc, char *argv[]) {

    X x1;

    X x2 = std::move(x1);
    X x3 = static_cast<X &&>(x2);

    do_stuff(X());
    X x;
    do_stuff(std::move(x));
    do_stuff(std::move(x));

    return 0;
}
