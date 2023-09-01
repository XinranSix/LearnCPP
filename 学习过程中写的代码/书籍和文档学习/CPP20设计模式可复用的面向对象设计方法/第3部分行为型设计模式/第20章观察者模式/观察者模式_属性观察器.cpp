#include <iostream>

struct Person {

    Person(int age) : age { age } {}

    int get_age() const { return age; }
    void set_age(int value) { age = value; }

private:
    int age {};
};

int main(int argc, char *argv[]) { return 0; }
