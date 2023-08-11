#include <iostream>

class Animal {
public:
    virtual ~Animal() = default;
};

class Dog : public Animal {};

class Bird : public Animal {};

// 酱紫是不好的行为
void speak(Animal const &animal) {
    if (typeid(animal) == typeid(Dog)) {
        std::cout << "Wo0f!" << std::endl;
    } else if (typeid(animal) == typeid(Bird)) {
        std::cout << "Chirp!" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    return 0;
}
