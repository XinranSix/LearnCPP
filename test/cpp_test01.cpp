#include <iostream>
#include <bitset>
#include <ostream>
#include <thread>

using namespace std;

int main() {

    std::thread t1([]() {
        for (int i = 0; i < 100; i += 2) {
            std::cout << i << std::endl;
        }
    });
    for (int i = 1; i < 100; i += 2) {
        std::cout << i << std::endl;
    }
    t1.join();
    return 0;
}
