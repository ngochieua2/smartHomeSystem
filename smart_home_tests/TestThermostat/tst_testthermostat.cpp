#include <QtTest>

// add necessary includes here
#include <realthermostat.h>
class TestThermostat : public QObject
{
    Q_OBJECT
    
public:
    TestThermostat();
    ~TestThermostat();
    
private slots:
    void initTestCase();
    void cleanupTestCase();
    void test5LastMeasurement();
    void testUnit();
};

TestThermostat::TestThermostat()
{
    
}

TestThermostat::~TestThermostat()
{
    
}

void TestThermostat::initTestCase()
{
    
}

void TestThermostat::cleanupTestCase()
{
    
}

void TestThermostat::test5LastMeasurement()
{
    RealThermostat realThermos{};
    QCOMPARE(realThermos.Last5Measurement().size(),5);
}

void TestThermostat::testUnit()
{
    
}


QTEST_APPLESS_MAIN(TestThermostat)

#include "tst_testthermostat.moc"
