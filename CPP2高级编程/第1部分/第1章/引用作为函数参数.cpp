#include <functional>
#include <iostream>

// void addOne(int i) { i++; }

void addOne(int &i) { i++; }

void swap(int &i, int &j) {
    int temp{i};
    i = j;
    j = temp;
}

struct X {};

struct Y : X {};

int main(int arvc, char *argv[]) {

    int myInt{7};
    addOne(myInt);

    int x{5}, y{6};
    swap(x, y);

    int *xp{&x}, *yp{&y};
    swap(*xp, *yp);

    X a{};
    Y b{};
    X &c{a};
    X &d{b};

    return 0;
}
