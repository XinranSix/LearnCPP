#include <chrono>
#include <iostream>

int main(int argc, char *argv[]) {

    auto begin { std::chrono::high_resolution_clock::now() };
    for (int i { 0 }; i < 10000; ++i) {
    }
    auto end { std::chrono::high_resolution_clock::now() };

    // std::cout <<
    // std::chrono::duration<double, std::chrono::seconds>(end - begin);
    //  << std::endl;

    return 0;
}
