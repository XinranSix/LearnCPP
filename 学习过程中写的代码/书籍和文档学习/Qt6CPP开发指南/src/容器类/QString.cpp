#include "qnamespace.h"
#include <QCoreApplication>
#include <ios>
#include <iostream>
#include <QString>
#include <QChar>

int main(int argc, char *argv[]) {

    {
        QString str { "Hello Qt" };
        qDebug() << str;
    }

    {
        QString str { "dimple,酒窝" };
        QChar ch0 { str[0] };
        QChar ch7 { str.at(7) };
        qDebug() << str;
    }

    {
        QString str { "Dimple" };
        QChar chP { QChar::fromLatin1('P') };
        // QChar chP { 'P' };
        str[0] = chP;
        qDebug() << str;
    }

    {
        QString str { "Hello,北京" };
        str[6] = QChar { 0x9752 };
        str[7] = QChar::fromUcs2(0x5C9B);
        qDebug() << str;
    }

    {
        QString HuStr { "河 to 湖" };
        QChar He { QChar::fromUcs2(HuStr[0].unicode()) };
        QChar Hu { HuStr[3].unicode() };
        QString str { "他们来自河南或河北" };
        for (int i {}; i < str.size(); ++i) {
            if (str.at(i) == He) {
                str[i] = Hu;
            }
        }
        qDebug() << str;
    }

    {
        QString str1 { "胡" }, str2 { "宇婷" };
        QString str3 { str1 + str2 };
        str1 = str2 + str1;
        qDebug() << str1;
        qDebug() << str2;
        qDebug() << str3;
    }

    {
        QString str1 { "卖" }, str2 { "拐" };
        QString str3 = str1;
        str1.append(str2);
        str3.prepend(str2);
    }

    {
        QString str1 { "hello world" };
        QChar ch1 { str1.front() };
        QChar ch2 { str1.back() };
        qDebug() << ch1;
        qDebug() << ch2;
    }

    {
        QString str1 { "G:\\Qt6Book\\QtSamples\\qw.cpp" };
        QString str2 { str1.left(2) };
        str2 = str1.right(3);
    }

    {
        // 同上，但更快，仅限于 Qt6
        QString str1 { "G:\\Qt6Book\\QtSamples\\qw.cpp" };
        QString str2 { str1.first(2) };
        str2 = str1.last(3);
    }

    {
        QString str1 { "G:\\Qt6Book\\QtSamples\\qw.cpp" };
        auto N { str1.lastIndexOf("\\") };
        QString str2 = { str1.mid(N + 1) };
    }

    {
        QString str1 { "G:\\Qt6Book\\QtSamples\\qw.cpp" };
        auto N { str1.lastIndexOf("\\") };
        QString str2 { str1.sliced(N + 1) };
        str2 = str1.sliced(N + 1, 2);
    }

    {
        QString str2, str1 { "学生姓名，男，2003-6-15，汉族，山东" };
        str2 = str1.section("，", 0, 0);
        str2 = str1.section("，", 1, 1);
        str2 = str1.section("，", 0, 1);
        str2 = str1.section("，", 4, 4);
    }

    {
        QString str1, str2 { "" };
        bool N = str1.isNull(); // true
        N = str2.isNull();      // false
        N = str1.isEmpty();     // true
        N = str2.isEmpty();     // true
    }

    {
        QString str1 { "NI好" };
        auto N { str1.count() };
        N = str1.size();
        N = str1.length();
    }

    {
        QString str1 { "" };
        bool N { str1.isNull() };
        std::cout << std::boolalpha << N << std::endl;
        N = str1.isEmpty();
        std::cout << std::boolalpha << N << std::endl;
        str1.clear();
        N = str1.isNull();
        std::cout << std::boolalpha << N << std::endl;
    }

    {
        QString str1;
        bool chk { str1.isNull() };
        str1.resize(5, '0');
    }

    {
        QString str1 { "Hello" };
        str1.fill('X');
        str1.fill('A', 2);
        str1.fill(QChar { 0x54c8 }, 3);
    }

    {
        QString str1 { "G:\\Qt6Book\\QtSamples\\qw.cpp" };
        auto N { str1.indexOf("Qt") };
        N = str1.lastIndexOf("\\");
    }

    {
        QString str1 { "G:\\Qt6Book\\QtSamples\\qw.cpp" };
        auto N { str1.contains(".cpp") };
        N = str1.contains(".CPP");
        N = str1.contains(".CPP", Qt::CaseInsensitive);
    }

    {
        QString str1 { "G:\\Qt6Book\\QtSamples\\qw.cpp" };
        auto N { str1.endsWith(".CPP", Qt::CaseInsensitive) };
        N = str1.endsWith(".CPP", Qt::CaseSensitive);
        N = str1.startsWith("g:");
    }

    {
        QString str1 { "G:\\Qt6Book\\QtSamples\\qw.cpp" };
        auto N { str1.count("Qt") };
        N = str1.count("QT");
        N = str1.count("QT", Qt::CaseInsensitive);
    }

    {
        QString str1 { "Hello, World" }, str2;
        str2 = str1.toUpper();
        str2 = str1.toLower();
    }

    {
        QString str1 { " Are          you              PK?     " }, str2;
        str2 = str1.trimmed();
        str2 = str1.simplified();
    }

    {
        QString str1 { "widget.cpp" };
        str1.chop(4);
    }

    {
        QString str1 { "It is great" };
        auto N { str1.lastIndexOf(" ") };
        str1.insert(N, "n't");
    }

    {
        QString str1 { "It is great" };
        auto N { str1.lastIndexOf(" ") };
        QString subStr { "wonderful" };
        str1.replace(N + 1, subStr.size(), subStr);
        str1.replace(N + 1, subStr.size(), "OK!");
    }

    {
        QString str1 { "Goooogle" };
        str1.replace('o', 'e');
    }

    {
        QString str1 { "G:\\Qt6Book\\QtSamples\\qw.cpp" };
        auto N { str1.lastIndexOf("\\") };
        str1.remove(N + 1, 20);
    }

    {
        QString str1 { "G:\\Qt6Book\\QtSamples\\qw.cpp" };
        QString DeStr { "\\" };
        QChar DeChar { DeStr[0].unicode() };
        str1.remove(DeChar);
    }

    {
        QString str = "153";
        int N { str.toInt() };

        bool ok {};
        str = "FF";
        N = str.toInt(&ok, 16);

        str = "10110111";
        N = str.toInt(&ok, 2);

        str = "0x5F";
        N = str.toInt(&ok, 0);
    }

    {
        QString str;
        double num { 1245.2783 };
        str.setNum(num, 'f', 5);
        str.setNum(num, 'E', 5);
        str.setNum(num, 'g', 5);
        str.setNum(num, 'g', 3);
    }

    {
        int N { 245 };
        QString str { QString::number(203) };
        str = QString::number(N, 16);
        double num { 365.263 };
        str = QString::number(num, 'f', 4);
        str = QString::number(num, 'E', 4);
    }

    {
        QString str1 { QString::asprintf("Year=%d,\tMonth=%2d,\tDay=%2d", 2021,
                                         6, 12) };
        QString UPC { "UPC" };
        QString str2 { QString::asprintf("Hello,欢迎来到 %d",
                                         UPC.toLocal8Bit().data()) };
        double pi { M_PI };
        QString str3 { QString::asprintf("Pi = %.10f", pi) };
    }

    {
        int Y { 2021 }, M { 8 }, D { 3 };
        int base { 10 };
        QChar ch { '0' };
        QString str1 { QString { "%1年%2月%3日" }
                           .arg(Y)
                           .arg(M, 2, base, ch)
                           .arg(D, 2, base, ch) };
    }

    {
        QString name { "张三" };
        int age { 25 };
        QString str2 { QString { "名字%1, 今年%2岁" }.arg(name).arg(age) };
    }

    {
        double pi { M_PI };
        int precision { 8 };
        QString str3 { QString { "pi=%1" }.arg(pi, 0, 'f', precision) };
    }

    return 0;
}
