#include <iostream>

template<int I>
struct CupBoard {
    void open();
    struct Shelf;
    static double total_weigt;
};

template<int I>
void CupBoard<I>::open() {}

template<int I>
double CupBoard<I>::total_weigt = 0.0;

int main(int arvc, char *argv[]) { return 0; }
