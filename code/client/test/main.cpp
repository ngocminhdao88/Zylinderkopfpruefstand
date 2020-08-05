#include <QtTest>
#include <QDebug>
//#include "testrampgenerator.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    const int SLOT_SIZE = 100;

//    TestRampGenerator testRampGenerator;

//    return QTest::qExec(&testRampGenerator, argc, argv);

    QVector<float> values(SLOT_SIZE);

    for (int i = 0; i < SLOT_SIZE; i++) {
        values[i] = i;
    }

    QFile file("data.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file); // we will serialize the data into the file

        out << values;
        values.clear();

        file.close();
        qDebug() << "write data to file";
    }

    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);

        in >> values;
        file.close();
        qDebug() << "read data from file";
    }

    for (int i = 0; i < SLOT_SIZE; i++) {
        qDebug() << values.at(i);
    }

    return app.exec();
}

