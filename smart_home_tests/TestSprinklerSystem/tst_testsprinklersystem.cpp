#include <QtTest>

// add necessary includes here
#include "realsprinklersystem.h"

class TestSprinklerSystem : public QObject
{
    Q_OBJECT
    
public:
    TestSprinklerSystem();
    ~TestSprinklerSystem();
private slots:
    void initTestCase();
    void cleanupTestCase();
    void testTurnOn();
    void testTurnOff();
    void testSchedule();
};

TestSprinklerSystem::TestSprinklerSystem()
{
    
}

TestSprinklerSystem::~TestSprinklerSystem()
{
    
}

void TestSprinklerSystem::initTestCase()
{
    
}

void TestSprinklerSystem::cleanupTestCase()
{
    
}

void TestSprinklerSystem::testTurnOn()
{
    RealSprinklerSystem sprinkler{};
    sprinkler.turnOn();
    QCOMPARE(sprinkler.getState(), "ON");
}

void TestSprinklerSystem::testTurnOff()
{
    RealSprinklerSystem sprinkler{};
    sprinkler.turnOff();
    QCOMPARE(sprinkler.getState(), "OFF");
}

void TestSprinklerSystem::testSchedule()
{
    RealSprinklerSystem sprinkler{};
    sprinkler.turnOn();
    sprinkler.schedule(50000,50000);
    QCOMPARE(sprinkler.getState(), "OFF");
    }

QTEST_APPLESS_MAIN(TestSprinklerSystem)

#include "tst_testsprinklersystem.moc"
