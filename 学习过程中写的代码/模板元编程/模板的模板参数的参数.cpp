#include <iostream>

template<template<typename T, T *> class Buf>
class Lexer {
    static char storage[5];
    Buf<char, &Lexer<Buf>::storage[0]> buf;
};

// template<template<typename T> class List>
// class Node {
//     static T *storage;
// };


int main(int arvc, char *argv[]) { return 0; }
