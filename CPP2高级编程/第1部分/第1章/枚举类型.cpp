#include <iostream>

enum class PieceType : unsigned long { King = 1, Queen, Rook = 10, Pawn };

enum class State { Unknow, Started, Finised };
enum class Error { None, BadInput, DiskFull, Unknow };

PieceType piece1{PieceType::King};
using enum PieceType;
PieceType piece2{Queen};
using PieceType::King;
PieceType piece3{King};

enum X { X1, X2, X3, X4 };

X x{X1};

// bool ok{false};
// enum Status { error, ok }; // Error

int main(int arvc, char *argv[]) {

    // if (PieceType::King==1) {} //Error

    return 0;
}
