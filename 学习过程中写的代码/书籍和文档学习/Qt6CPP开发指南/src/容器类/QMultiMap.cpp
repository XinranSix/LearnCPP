#include <QCoreApplication>
#include <QMultiMap>
#include <iostream>
#include <QString>
#include <QList>

int main(int argc, char *argv[]) {

    QMultiMap<QString, int> map1, map2, map3;
    map1.insert("plenty", 100);
    map1.insert("plenty", 2000);
    map2.insert("plenty", 5000);
    map3 = map1 + map2;

    QList<int> values { map3.values("plenty") };
    for (int i { 0 }; i < values.size(); ++i) {
        std::cout << values[i] << std::endl;
    }

    return 0;
}
