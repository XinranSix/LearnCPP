#include <iostream>
#include <QList>
#include <QString>
#include <QDebug>
#include <QMap>

int main(int argc, char *argv[]) {

    QList<QString> list;
    list << "A"
         << "B"
         << "C"
         << "D";
    for (auto i { list.constBegin() }; i != list.constEnd(); ++i) {
        qDebug() << *i;
    }

    for (auto i { list.rbegin() }; i != list.rend(); ++i) {
        *i = i->toLower();
    }

    for (auto i { list.constBegin() }; i != list.constEnd(); ++i) {
        qDebug() << *i;
    }

    /* ---------------------------------------------------------------------- */
    QMap<int, int> map;
    for (auto i { map.constBegin() }; i != map.constEnd(); ++i) {
        qDebug() << i.key() << ":" << i.value();
    }

    {
        QList<QString> list;
        QString str;
        foreach (str, list)
            qDebug() << str;
    }

    {
        QList<QString> list;
        foreach (const QString str, list) {
            if (str.isEmpty()) {
                break;
            }
            qDebug() << str;
        }
    }

    {
        QMap<QString, int> map;
        foreach (const QString str, map.keys()) {
            qDebug() << str << ":" << map.value(str);
        }
    }

    {
        QMultiMap<QString, int> map;
        foreach (const QString str, map.uniqueKeys()) {
            foreach (int i, map.values(str)) {
                qDebug() << str << ":" << i;
            }
        }
    }

    return 0;
}
