#include <QtTest>

// add necessary includes here
#include "reallightswitch.h"

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
    RealLightSwitch light{};
    light.turnOn();
    QCOMPARE(light.getState(), true);
}

void TestLightSwitch::testTurnOff()
{
    RealLightSwitch light{};
    light.turnOff();
    QCOMPARE(light.getState(), false);    
}

void TestLightSwitch::testDim()
{
    RealLightSwitch light{};
    light.setBrightnessLevel(40);
    light.dim();
    QCOMPARE(light.getBrightnessLevel(),20);
    light.dim();
    QCOMPARE(light.getBrightnessLevel(),20);
}

void TestLightSwitch::testBrighten()
{
    RealLightSwitch light{};
    light.setBrightnessLevel(40);
    light.brighten();
    QCOMPARE(light.getBrightnessLevel(),60);
    light.setBrightnessLevel(100);
    light.brighten();
    QCOMPARE(light.getBrightnessLevel(),100);
}

QTEST_APPLESS_MAIN(TestLightSwitch)

#include "tst_testlightswitch.moc"
