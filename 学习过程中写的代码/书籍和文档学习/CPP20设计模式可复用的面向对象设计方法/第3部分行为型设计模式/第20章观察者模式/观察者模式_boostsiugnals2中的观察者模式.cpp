#include <format>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>
#include <algorithm>
#include "boost/signals2.hpp"

template <typename T>
struct Observer {
    virtual void field_changed(T &source, std::string const &filed_name) = 0;
};

template <typename T>
struct Observable {
    boost::signals2::signal<void(T &, std::string const &)> propert_changed;

private:
};

struct Person : Observable<Person> {

    Person(int age) : age { age } {}

    int get_age() const { return age; }
    void set_age(int value) {
        if (age == value) {
            return;
        }
        age = value;
        propert_changed(*this, "age");
    }

private:
    int age {};
};

int main(int argc, char *argv[]) {

    Person p { 123 };
    auto conn { p.propert_changed.connect(
        [](Person &, std::string const &prop_name) {
            std::cout << prop_name << " has been changed" << std::endl;
        }) };

    p.set_age(20);
    conn.disconnect();

    return 0;
}
