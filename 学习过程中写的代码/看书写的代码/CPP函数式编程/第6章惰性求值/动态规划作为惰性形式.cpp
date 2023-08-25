#include <algorithm>
#include <iostream>
#include <string>

unsigned int lev(unsigned int m, unsigned int n, std::string const &a, std::string const &b) {
    return m == 0   ? n
           : n == 0 ? m
                    : std::min({ lev(m - 1, n, a, b) + 1, lev(m, n - 1, a, b) + 1,
                                 lev(m - 1, n - 1, a, b) + (a[m - 1] != b[n - 1]) });
}

int main(int argc, char *argv[]) {
    return 0;
}
