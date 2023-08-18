#include <iostream>
#include <string>

using namespace std;

template <typename T>
concept Incrementable = requires(T x) {
    x++;
    ++x;
};

Incrementable auto value1 { 1 };
// Incrementable auto value2 { "abc"s }; // Error

int main(int argc, char *argv[]) {
    return 0;
}
