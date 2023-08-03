#include <iostream>
#include <string>

template<typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}

int main(int arvc, char *argv[]) {

    std::string a;
    ::max("apple", "peach");
    ::max("apple", "tomato");
    // ::max("apple", s);

    return 0;
}
