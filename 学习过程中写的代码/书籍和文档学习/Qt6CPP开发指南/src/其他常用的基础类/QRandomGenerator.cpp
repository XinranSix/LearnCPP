#include <QCoreApplication>
#include <QRandomGenerator>
#include <iostream>
#include <QDateTime>
#include <QList>

int main(int argc, char *argv[]) {

    {
        QRandomGenerator *rand1 { new QRandomGenerator {
            static_cast<quint32>(QDateTime::currentMSecsSinceEpoch()) } };
        QRandomGenerator *rand2 { new QRandomGenerator {
            static_cast<quint32>(QDateTime::currentSecsSinceEpoch()) } };

        for (int i {}; i < 5; ++i) {
            qDebug("R1=%u, R2=%u", rand1->generate(), rand2->generate());
        }
    }

    // 你最好酱紫做👿
    { auto rand { QRandomGenerator::global()->generate() }; }

    {
        QRandomGenerator rnad { static_cast<quint32>(
            QDateTime::currentSecsSinceEpoch()) };
        for (int i {}; i < 5; ++i) {
            qDebug("number = %u", rand());
        }
    }

    {
        QList<quint32> list;
        list.resize(20);
        QRandomGenerator::global()->fillRange(list.data(), list.size());

        quint32 array[10];
        QRandomGenerator::global()->fillRange(array);
    }

    {
        for (int i {}; i < 10; ++i) {
            quint32 score { static_cast<quint32>(
                QRandomGenerator::global()->bounded(60, 101)) };
            qDebug("score = %u", score);
        }
    }

    return 0;
}
