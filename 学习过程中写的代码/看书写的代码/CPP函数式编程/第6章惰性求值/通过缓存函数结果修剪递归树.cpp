#include <iostream>
#include <vector>

std::vector<unsigned int> cache { 0, 1 };

unsigned int fib(unsigned int n) {
    if (cache.size() > n) {
        return cache[n];
    } else {
        auto const result = fib(n - 1) + fib(n - 2);
        cache.push_back(result);
        return result;
    }
}

int main(int argc, char *argv[]) {
    return 0;
}
