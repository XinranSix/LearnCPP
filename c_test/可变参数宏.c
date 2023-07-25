#include <stdio.h>

#define LOG(fmt, args...) printf(fmt, ##args)
// #define LOG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define DEBUG(...) printf(__VA_ARGS__)

// #define A(x) a##x

int main() {

    LOG("Hello! I'm %s\n", "Yao J");
    DEBUG("Hello! I'm %s\n", "Yao J");

    LOG("hello\n");

    return 0;
}
