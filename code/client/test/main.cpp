#include <QtTest>
#include "testrampgenerator.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    TestRampGenerator testRampGenerator;

    return QTest::qExec(&testRampGenerator, argc, argv);
}

