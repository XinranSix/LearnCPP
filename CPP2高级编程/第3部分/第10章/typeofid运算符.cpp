#include <iostream>
#include <string>

class Loggable {
public:
    virtual ~Loggable() = default;
    virtual std::string getLogMessage() const = 0;
};

class Foo : public Loggable {
public:
    std::string getLogMessage() const override {
        return "Hello logger.";
    }
};

void logObject(Loggable const &loggableObject) {
    std::cout << typeid(loggableObject).name() << std::endl;
    std::cout << loggableObject.getLogMessage() << std::endl;
}

int main(int argc, char *argv[]) {

    logObject(Foo {});

    return 0;
}
