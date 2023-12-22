#include <QCoreApplication>
#include <QQueue>
#include <iostream>

int main(int argc, char *argv[]) {

    QQueue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    while (!queue.isEmpty()) {
        std::cout << queue.dequeue() << std::endl;
    }

    return 0;
}
