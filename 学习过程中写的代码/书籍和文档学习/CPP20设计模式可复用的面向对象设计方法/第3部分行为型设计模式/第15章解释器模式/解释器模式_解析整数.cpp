#include <iostream>

int beeter_atoi(const char *str) {
    int val { 0 };
    while (*str) {
        val = val * 10 + (*str++ - '0');
    }
    return val;
}

int main(int argc, char *argv[]) { return 0; }
