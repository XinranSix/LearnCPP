#include <iostream>
#include <gtest/gtest.h>
#include <string>

class Something {
public:
    Something() {
        std::cout << "2" << std::endl;
    }
    virtual ~Something() {
        std::cout << "D: 2" << std::endl;
    }
};

class Base {
public:
    Base() {
        std::cout << "1" << std::endl;
    }
    virtual ~Base() {
        std::cout << "D: 1" << std::endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "3" << std::endl;
    }
    virtual ~Derived() {
        std::cout << "D: 3" << std::endl;
    }

private:
    Something m_dataMember;
};

TEST(利用父类, 构造顺序) {
    Derived myDerived;
}

TEST(利用父类, 析构函数) {
    Base *ptr { new Derived {} };
    delete ptr;
}

class Book {
public:
    virtual ~Book() = default;
    virtual std::string getDescription() const {
        return "Book";
    };
    virtual int getHeight() const {
        return 120;
    }
};

class Paperback : public Book {
public:
    std::string getDescription() const override {
        return "Paperback " + Book::getDescription();
    };
};

class Romance : public Paperback {
public:
    std::string getDescription() const override {
        return "Romance " + Paperback::getDescription();
    }
    int getHeight() const override {
        return Paperback::getHeight() / 2;
    }
};

class Technical : public Book {
public:
    std::string getDescription() const override {
        return "Technical " + Book::getDescription();
    }
};

TEST(利用父类, 使用父类方法) {
    Romance novel;
    Book book;
    std::cout << novel.getDescription() << std::endl;
    std::cout << book.getDescription() << std::endl;
    std::cout << novel.getHeight() << std::endl;
    std::cout << book.getHeight() << std::endl;
}



int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
