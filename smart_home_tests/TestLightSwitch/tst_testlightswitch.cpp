#include <QtTest>

// add necessary includes here

class TestLightSwitch : public QObject
{
    Q_OBJECT
    
public:
    TestLightSwitch();
    ~TestLightSwitch();
    
private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
    
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

void TestLightSwitch::test_case1()
{
    
}

QTEST_APPLESS_MAIN(TestLightSwitch)

#include "tst_testlightswitch.moc"
