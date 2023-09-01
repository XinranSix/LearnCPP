#include <format>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
struct Observer {
    virtual void field_changed(T &source, std::string const &filed_name) = 0;
};

template <typename T>
struct Observable {
    void notify(T &source, std::string const &name) {
        for (auto obs : observers) {
            obs->field_changed(source, name);
        }
    }

    void subscribe(Observer<T> *f) { observers.push_back(f); }

    void unsubscribe(Observer<T> *f) {}

private:
    std::vector<Observer<T> *> observers;
};

struct Person : Observable<Person> {

    Person(int age) : age { age } {}

    int get_age() const { return age; }
    void set_age(int value) {
        if (this->age == value) {
            return;
        }
        this->age = value;
        notify(*this, "age");
    }

private:
    int age {};
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

int main(int argc, char *argv[]) { return 0; }
