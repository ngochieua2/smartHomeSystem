#include <QtTest>

// add necessary includes here
#include <realsprinklersystem.h>

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
    RealSprinklerSystem realSprinkler{};
    realSprinkler.turnOn();
    QCOMPARE(realSprinkler.getState(),"ON");
}

void TestSprinklerSystem::testTurnOff()
{
    RealSprinklerSystem realSprinkler{};
    realSprinkler.turnOff();
    QCOMPARE(realSprinkler.getState(),"OFF");
}

void TestSprinklerSystem::testSchedule()
{
    RealSprinklerSystem realSprinkler{};
    realSprinkler.schedule(100,100);
    QCOMPARE(realSprinkler.getState(),"SCHEDULED");
    
}

QTEST_APPLESS_MAIN(TestSprinklerSystem)

#include "tst_testsprinklersystem.moc"
