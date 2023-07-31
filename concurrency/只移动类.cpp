#include <iostream>
#include <memory>

template<class T>
class move_only {
    std::unique_ptr<T> data;

public:
    move_only(move_only const &) = delete;
    move_only(move_only &&other) : data(std::move(data)) {}
    move_only &operator=(move_only &) = delete;
    move_only &operator=(move_only &&other) {
        data = std::move(other.data);
        return *this;
    }
};

int main(int arvc, char *argv[]) { return 0; }
