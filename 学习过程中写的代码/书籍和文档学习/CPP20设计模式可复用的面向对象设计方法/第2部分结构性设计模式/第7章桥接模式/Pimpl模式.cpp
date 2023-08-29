#include "fmt/core.h"
#include <iostream>
#include <memory>
#include <string>

struct Person {
    std::string name;

    void greet();

    Person();

    // ~Person();

    struct PersonImpl;
    std::unique_ptr<PersonImpl> impl;
};

struct Person::PersonImpl {
    void greet(Person *p);
};

Person::Person() : impl { new PersonImpl } {}

void Person::greet() { impl->greet(this); }

void Person::PersonImpl::greet(Person *p) { fmt::print("hello {}", p->name); }

int main(int argc, char *argv[]) { 
    
    

    
    return 0; }
