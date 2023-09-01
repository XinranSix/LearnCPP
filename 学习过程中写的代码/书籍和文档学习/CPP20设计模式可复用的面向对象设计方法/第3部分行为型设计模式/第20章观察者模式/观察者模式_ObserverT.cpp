#include <format>
#include <iostream>
#include <string>

struct Person {

    Person(int age) : age { age } {}

    int get_age() const { return age; }
    void set_age(int value) { age = value; }

private:
    int age {};
};

template <typename T>
struct Observer {
    virtual void field_changed(T &source, std::string const &filed_name) = 0;
};

struct ConsolePersonObserver : Observer<Person> {
    virtual void field_changed(Person &source,
                               std::string const &filed_name) override {
        if (filed_name == "age") {
            std::cout << std::format("Person's age has changed to {}.\n",
                                     source.get_age());
        }
    }
};

/* struct PersonLister {
    virtual void person_changed(Person &p,
                                std::string const &property_name) = 0;
}; */

int main(int argc, char *argv[]) { return 0; }
