#include <iostream>

int main(int arvc, char *argv[]) {

    int *myIntegerPointer{nullptr};
    myIntegerPointer = new int;

    *myIntegerPointer = 8;
    delete myIntegerPointer;
    myIntegerPointer = nullptr;

    int i{8};
    int *myIntegerPointer2{&i};

    return 0;
}
