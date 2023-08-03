#include <iostream>
#include <string>

template<typename T>
inline T const &max(T const &a, T const &b) {
    return a < b ? b : a;
}

int main(int arvc, char *argv[]) {

    std::string s;
    ::max("apple", "peach");
    // ::max("apple", "tomato");
    // ::max("apple", s);

    return 0;
}
