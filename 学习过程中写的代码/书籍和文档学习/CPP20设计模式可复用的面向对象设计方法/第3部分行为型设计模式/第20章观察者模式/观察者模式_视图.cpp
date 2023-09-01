#include <format>
#include <iostream>
#include <mutex>
#include <string>
#include <utility>
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

struct Person {
    std::string name;
};

struct PersonView : Observable<Person> {
    explicit PersonView(Person &person) : person { person } {}

    std::string &get_name() { return person.name; }

    void set_name(std::string value) {
        if (value != person.name) {
            return;
        }
        person.name = std::move(value);
        propert_changed(person, "name");
    }

protected:
    Person &person;
};

int main(int argc, char *argv[]) {

    /*    Person p { 123 };
       auto conn { p.propert_changed.connect(
           [](Person &, std::string const &prop_name) {
               std::cout << prop_name << " has been changed" << std::endl;
           }) };

       p.set_age(20);
       conn.disconnect();
    */
    return 0;
}
