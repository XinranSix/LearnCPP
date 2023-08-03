#include <iostream>

template<typename T>
union AllocChunk {
    T object;
    unsigned char bytes[sizeof(T)];
};

int main(int arvc, char *argv[]) { return 0; }
