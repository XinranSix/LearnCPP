#include <QCoreApplication>
#include <QSet>
#include <iostream>
#include <QString>

int main(int argc, char *argv[]) {

    QSet<QString> set;
    set << "dog"
        << "cat"
        << "tiger";

    return 0;
}
