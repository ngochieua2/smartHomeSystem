#include <QtTest>

// add necessary includes here
#include "lightswitchproxy.h"
#include "thermostatproxy.h"
#include "sprinklersystemproxy.h"
#include "controllerproxy.h"
#include "reallightswitch.h"
#include "realcontroller.h"
#include "realthermostat.h"
#include "realsprinklersysem.h"

class TestProxyClasses : public QObject
{
    Q_OBJECT
    
public:
    TestProxyClasses();
    ~TestProxyClasses();
    
private slots:
    void initTestCase();
    void cleanupTestCase();
    void testProxyCreation();
    void testChangeState();
};

TestProxyClasses::TestProxyClasses()
{
    
}

TestProxyClasses::~TestProxyClasses()
{
    
}

void TestProxyClasses::initTestCase()
{
    
}

void TestProxyClasses::cleanupTestCase()
{
    
}

void TestProxyClasses::testProxyCreation()
{
    //RealLightSwitch* realLight{};
    //LightSwitchProxy lightProxy("id",QUrl("/state"));
    //lightProxy.setRealLight(realLight);
    //lightProxy.turnOn();
    //QCOMPARE(lightProxy.getState(),realLight->getState());
    
}

void TestProxyClasses::testChangeState()
{
    
}


QTEST_APPLESS_MAIN(TestProxyClasses)

#include "tst_testproxyclasses.moc"
