#include <iostream>
#include <gtest/gtest.h>

struct Foo {};

struct Bar {};

struct Baz : public Foo, public Bar {};

struct Dog {
    virtual void bark() {
        std::cout << "Woof!" << std::endl;
    }

    virtual void eat() {
        std::cout << "The dog ate." << std::endl;
    }
};

struct Bird {
    virtual void chirp() {
        std::cout << "Chirp!" << std::endl;
    }

    virtual void eat() {
        std::cout << "The bird ate." << std::endl;
    }
};

struct DogBird : Dog, Bird {
    void eat() override {
        Dog::eat();
    }
};

TEST(多重继承, 从多个类继承) {
    DogBird myConfuseAniaml;
    myConfuseAniaml.bark();
    myConfuseAniaml.chirp();
}

TEST(多重继承, 名称冲突) {
    DogBird myConfuseAniaml;
    // myConfuseAniaml.eat();// Error
    dynamic_cast<Dog &>(myConfuseAniaml).eat();
    myConfuseAniaml.Dog::eat();
}

TEST(多重继承, 歧义基类) {
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
