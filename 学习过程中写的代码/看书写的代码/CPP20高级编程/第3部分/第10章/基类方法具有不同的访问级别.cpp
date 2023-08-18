#include <iostream>

struct Secret {
protected:
    virtual void dontTell() {
        std::cout << "I'll never tell." << std::endl;
    }
};

struct Blabber : public Secret {
public:
    using Secret::dontTell;
};

int main(int argc, char *argv[]) {

    Blabber myBlabber;
    Secret &ref { myBlabber };
    Secret *ptr { &myBlabber };
    myBlabber.dontTell();
    // ref.dontTell();// Error
    // ptr->dontTell(); // Error

    return 0;
}
