#include <format>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
struct Observer {
    virtual void field_changed(T &source, std::string const &filed_name) = 0;
};

template <typename T>
struct Observable {
    void notify(T &source, std::string const &name) {
        std::scoped_lock<std::mutex> lock { mtx };
        for (auto obs : observers) {
            // obs->field_changed(source, name);
        }
    }

    void subscribe(Observer<T> *f) {
        std::scoped_lock<std::mutex> lock { mtx };
        observers.push_back(f);
    }

    void unsubscribe(Observer<T> *f) {
        std::scoped_lock<std::mutex> lock { mtx };
        observers.erase(std::remove(observers.begin(), observers.end(), f),
                        observers.end());
    }

private:
    std::vector<Observer<T> *> observers;
    std::mutex mtx;
};

struct Person : Observable<Person> {

    Person(int age) : age { age } {}

    int get_age() const { return age; }
    void set_age(int value) {
        if (age == value) {
            return;
        }
        auto old_can_vote { get_can_vote() };
        age = value;
        notify(*this, "age");

        if (old_can_vote != get_can_vote()) {
            notify(*this, "can_vote");
        }
    }

    bool get_can_vote() const { return age >= 16; }

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

struct TrafficAdministration : Observer<Person> {
    void field_changed(Person &source, std::string const &filed_name) override {
        if (filed_name == "age") {
            std::cout << "Whoa there, you are not old enough to drive!\n";
        } else {
            std::cout << "We no longer care!\n";
            source.unsubscribe(this);
        }
    };
};

int main(int argc, char *argv[]) {

    Person p { 20 };
    ConsolePersonObserver cpo;
    p.subscribe(&cpo);
    p.set_age(21);
    p.set_age(22);

    return 0;
}
