#include <iostream>

class Manager {
    template<typename T>
    friend class Task;

    // template<typename T>
    // friend void Schedule<T>::dispatch(Task<T> *);

    template<typename T>
    friend int ticket() {
        return ++Manager::counter;
    }

    static int counter;
};

int main(int arvc, char *argv[]) { return 0; }
