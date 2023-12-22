#include <QCoreApplication>
#include <QMap>
#include <iostream>
#include <QString>

int main(int argc, char *argv[]) {

    QMap<QString, int> map;
    map["one"] = 1;
    map["two"] = 2;
    map["three"] = 3;

    map.insert("four", 4);
    map.remove("two");

    int num1 { map["one"] };
    int num2 { map.value("two") };
    auto timeout { map.value("TIMEOUT", 30) };

    return 0;
}
