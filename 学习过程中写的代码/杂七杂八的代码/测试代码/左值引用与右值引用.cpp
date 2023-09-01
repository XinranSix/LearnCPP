#include <algorithm>
#include <cstddef>
#include <format>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

template <typename T>
class MyArr {

    using size_type = size_t;
    using value_type = T;

    MyArr(size_type capacity = 0)
        : m_size { capacity }, m_capacity { capacity },
          arr { new T[m_capacity] } {}

    MyArr(std::initializer_list<T> values) : MyArr { values.size() } {
        for (size_t i { 0 }; i < m_capacity; ++i) {
            arr[i] = values[i];
        }
    }

    MyArr(MyArr<T> const &other) : MyArr { other.m_size } {
        for (size_t i { 0 }; i < m_capacity; ++i) {
            arr[i] = other.arr[i];
        }
    }

    MyArr<T> &operator=(MyArr<T> const &other) {
        MyArr<T> tmp { other };
        swap(*this, other);
        return *this;
    }

    MyArr(MyArr<T> const &&other) noexcept { swap(other, *this); }

    MyArr<T> &operator=(MyArr<T> const &&other) noexcept {
        swap(*this, other);
        return *this;
    }

    ~MyArr() {
        if (arr != nullptr) {
            delete[] arr;
            arr = nullptr;
        }
        m_capacity = 0;
        m_size = 0;
    }

private:
    T *arr {};
    size_type m_capacity {};
    size_type m_size {};

    void swap(T const &other) noexcept {
        arr = std::exchange(other.arr, nullptr);
        m_capacity = std::exchange(other.m_capacity, 0);
        m_size = std::exchange(other.m_size, 0);
    }
};

int main(int argc, char *argv[]) { return 0; }
