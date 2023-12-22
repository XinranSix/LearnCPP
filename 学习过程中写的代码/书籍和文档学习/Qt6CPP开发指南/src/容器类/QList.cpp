#include <QCoreApplication>
#include <QList>
#include <QString>

int main(int argc, char *argv[]) {

    QList<float> list1;
    QList<int> list2 { 1, 2, 3, 4, 5 };
    QList<int> list3(100);
    QList<QString> strList(10, "pass");

    QList<QString> list;
    list << "Monday"
         << "Tuesday"
         << "Wednesday"
         << "Thursday";
    list.append("Friday");
    QString str1 { list[0] };
    QString str2 { list.at(1) };

    return 0;
}
