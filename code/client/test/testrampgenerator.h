#ifndef TESTRAMPGENERATOR_H
#define TESTRAMPGENERATOR_H

#include <QObject>
#include <QtTest>
#include "rampgenerator.h"

class TestRampGenerator : public QObject
{
    Q_OBJECT

private slots:
    //functions executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    //functions executed by QtTest before and after each test
    void init();
    void cleanup();

    //test function - all functions frefixed with "test" will be ran as test
    void testFirstRun();
    void testRampUp();
    void testRampUpRate();
    void testRamp_data();
    void testRamp();
    void testRampEnable();


    //some help functions

private:
    RampGenerator m_ramp;
};

#endif // TESTRAMPGENERATOR_H
