#include <iostream>
#include <gtest/gtest.h>

class Base {
public:
    // 如果父类方法标记为 virtual，则其子类中继承到的此方法都会被自动标记标记为
    // virtual
    virtual void someMethod() {
        std::cout << "基类的 someMethod 方法" << std::endl;
    }

protected:
    int m_protectedInt { 0 };

private:
    int m_privateInt;
};

class Derived : public Base {
public:
    void someMethod() override {
        std::cout << "子类的 someMethod 方法" << std::endl;
    }

    void someOtherMethod() {
        std::cout << "I can access base class data member m_protectedInt."
                  << std::endl;
        std::cout << "Its value is " << m_protectedInt << std::endl;
        // std::cout << "The value of m_privateInt is " << m_privateInt
        //           << std::endl; // Error
    }
};

class Derived1 : public Base {
public:
    void someOtherMethod() {
    }
};

class Derived2 : public Base {
public:
    void someOtherMethod() {
    }
};

class DerivedDerived : public Derived {};

TEST(拓展类, 继承) {
    Derived myDerived;
    myDerived.someMethod();
    myDerived.someOtherMethod();

    Base myBase;
    myBase.someMethod();

    Base *base { new Derived {} };
    // base->someOtherMethod(); // Error
}

/* -------------------------------------------------------------------------- */
// 禁用继承
class Foo final {};

// class X : Foo {}; // Error
/* -------------------------------------------------------------------------- */

TEST(拓展类, 重写方法) {
    Base myBase;
    myBase.someMethod();

    Derived myDerived;
    myDerived.someMethod();

    Base &ref { myDerived };
    ref.someMethod();

    Base assignedObject { myDerived };
    assignedObject.someMethod();
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
