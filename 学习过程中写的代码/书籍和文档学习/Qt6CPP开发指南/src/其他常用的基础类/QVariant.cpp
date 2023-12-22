#include <QVariant>
#include <QCoreApplication>
#include <iostream>

int main(int argc, char *argv[]) {

    QVariant var { 173 };
    QString str { var.toString() };
    int val { var.value<int>() };

    QStringList strList;
    strList << "One"
            << "Two"
            << "Three";
    var.setValue(strList);
    QStringList value { var.toStringList() };

    return 0;
}
