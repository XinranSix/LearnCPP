#include <QCoreApplication>
#include <QStack>
#include <QString>
#include <iostream>

int main(int argc, char *argv[]) {

    QStack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    while (!stack.isEmpty()) {
        std::cout << stack.pop() << std::endl;
    }

    return 0;
}
