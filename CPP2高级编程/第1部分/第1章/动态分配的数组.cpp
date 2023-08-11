#include <iostream>

int main(int arvc, char *argv[]) {

    int arraySize{8};
    int *myVariablesizeArray{new int[8]};

    myVariablesizeArray[3] = 2;

    delete[] myVariablesizeArray;
    myVariablesizeArray = nullptr;

    return 0;
}
