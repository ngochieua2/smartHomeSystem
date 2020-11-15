#include <QtTest>

// add necessary includes here
#include <reallightswitch.h>

class TestLightSwitch : public QObject
{
    Q_OBJECT
    
public:
    TestLightSwitch();
    ~TestLightSwitch();
    
private slots:
    void initTestCase();
    void cleanupTestCase();
    void testTurnOn();
    void testTurnOff();
    void testDim();
    void testBrighten();
};

TestLightSwitch::TestLightSwitch()
{
    
}

TestLightSwitch::~TestLightSwitch()
{
    
}

void TestLightSwitch::initTestCase()
{
    
}

void TestLightSwitch::cleanupTestCase()
{
    
}

void TestLightSwitch::testTurnOn()
{
    RealLightSwitch realLight{};
    realLight.turnOn();
    QCOMPARE(realLight.getState(), true);
}

void TestLightSwitch::testTurnOff()
{
    RealLightSwitch realLight{};
    realLight.turnOff();
    QCOMPARE(realLight.getState(), false);
}

void TestLightSwitch::testDim()
{
    RealLightSwitch realLight{};
    realLight.dim();
    QCOMPARE(realLight.getBrightness(), 20);
}

void TestLightSwitch::testBrighten()
{
    RealLightSwitch realLight{};
    realLight.brighten();
    QCOMPARE(realLight.getBrightness(), 70);
}

QTEST_APPLESS_MAIN(TestLightSwitch)

#include "tst_testlightswitch.moc"
