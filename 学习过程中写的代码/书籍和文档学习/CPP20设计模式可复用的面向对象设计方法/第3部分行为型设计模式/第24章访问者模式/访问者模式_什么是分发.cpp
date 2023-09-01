#include <iostream>

struct Stuff {
    virtual void call() = 0;
};

struct Foo;
struct Bar;

void func(Foo *foo);
void func(Bar *bar);

struct Foo : Stuff {
    virtual void call() override { func(this); }
};
struct Bar : Stuff {
    virtual void call() override { func(this); }
};

void func(Foo *foo) {}
void func(Bar *bar) {}

int main(int argc, char *argv[]) {

    Stuff *stuff = new Foo {};
    stuff->call();

    return 0;
}
