#include <iostream>

class fib_cache {
public:
    fib_cache() : m_previous { 0 }, m_last { 1 }, m_size { 2 } {}

    size_t size() const {
        return m_size;
    }

    unsigned int operator[](unsigned int n) const {
        return n == m_size - 1   ? m_last
               : n == m_size - 2 ? m_previous
                                 : throw std::out_of_range("The value is no longer in the cache");
    }

    void push_back(unsigned int value) {
        m_size++;
        m_previous = m_last;
        m_last = value;
    }

private:
    unsigned int m_previous;
    unsigned int m_last;
    size_t m_size;
} cache;

unsigned int fib1(unsigned int n) {
    if (cache.size() > n) {
        return cache[n];
    } else {
        const auto result = fib1(n - 1) + fib1(n - 2);
        cache.push_back(result);
        return result;
    }
}

int main(int argc, char *argv[]) {
    return 0;
}
