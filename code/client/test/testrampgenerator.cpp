#include "testrampgenerator.h"

void TestRampGenerator::initTestCase()
{
}

void TestRampGenerator::cleanupTestCase()
{
}

void TestRampGenerator::init()
{
}

void TestRampGenerator::cleanup()
{
}

void TestRampGenerator::testFirstRun()
{
    RampGenerator ramp;
    ramp.setStartValue(10);
    ramp.setEnable(true);
    ramp.calculateRamp();

    QCOMPARE(ramp.output(), 10);
}

void TestRampGenerator::testRampUp()
{
    RampGenerator ramp;
    ramp.setStartValue(10);
    ramp.setTargetValue(20);
    ramp.setEnable(true);

    ramp.calculateRamp(); //output should be 10
    QCOMPARE(ramp.output(), 10);

    ramp.calculateRamp(); //output should be 11
    QCOMPARE(ramp.output(), 11);

}

void TestRampGenerator::testRampUpRate()
{
    RampGenerator ramp;
    ramp.setStartValue(10);
    ramp.setTargetValue(20);
    ramp.setRampUpRate(5);
    ramp.setEnable(true);

    ramp.calculateRamp(); //output should be 10
    QCOMPARE(ramp.output(), 10);

    ramp.calculateRamp(); //output should be 15
    QCOMPARE(ramp.output(), 15);

    ramp.calculateRamp(); //output should be 20
    QCOMPARE(ramp.output(), 20);

    ramp.calculateRamp(); //output should stay at 20
    QCOMPARE(ramp.output(), 20);
}

void TestRampGenerator::testRamp_data()
{
    QTest::addColumn<double>("setpoint");
    QTest::addColumn<double>("rate");
    QTest::addColumn<double>("result");

    QTest::addRow("1. run") << 30.0 << 10.0 << 0.0;
    QTest::addRow("2. run") << 30.0 << 10.0 << 10.0;
    QTest::addRow("3. run") << 30.0 << 10.0 << 20.0;
    QTest::addRow("4. run") << 30.0 << 10.0 << 30.0;
    QTest::addRow("5. run") << 30.0 << 5.0 << 30.0;
    QTest::addRow("6. run") << 35.0 << -5.0 << 35.0; //rate should be positiv
    QTest::addRow("7. run") << 20.0 << 10.0 << 25.0;
    QTest::addRow("8. run") << 20.0 << 10.0 << 20.0;
    QTest::addRow("9. run") << 0.0 << 10.0 << 10.0;
    QTest::addRow("10. run") << 0.0 << 10.0 << 0.0;
    QTest::addRow("11. run") << -10. << 10.0 << -10.0;
    QTest::addRow("12. run") << 0.0 << 10.0 << 0.0; //ramp back up
    QTest::addRow("13. run") << 10.0 << 10.0 << 10.0; //ramp back up
}

void TestRampGenerator::testRamp()
{
    QFETCH(double, setpoint);
    QFETCH(double, rate);
    QFETCH(double, result);

    m_ramp.setTargetValue(setpoint);
    m_ramp.setStartValue(0);
    m_ramp.setRampUpRate(rate);
    m_ramp.setRampDownRate(rate);
    m_ramp.setEnable(true);

    m_ramp.calculateRamp();
    QCOMPARE(m_ramp.output(), result);
}


void TestRampGenerator::testRampEnable()
{
    RampGenerator ramp;
    ramp.setStartValue(10);
    ramp.setTargetValue(20);
    ramp.setRampUpRate(5);

    ramp.calculateRamp(); //output should be 0, cause ramp is not enabled
    QCOMPARE(ramp.output(), 0.0);

    ramp.calculateRamp(); //output should be 0, cause ramp is not enabled
    QCOMPARE(ramp.output(), 0.0);
}
