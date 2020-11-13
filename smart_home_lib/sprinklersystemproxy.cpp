#include "sprinklersystemproxy.h"

SprinklerSystemProxy::SprinklerSystemProxy(QString id, QUrl url)
{
    _device_id = id;
    _devideType = "sprinklerSystem";
    _deviceUrl = url;
}

SprinklerSystemProxy::~SprinklerSystemProxy()
{
    delete _realSprinklerSystem;
}

void SprinklerSystemProxy::turnOn()
{
    _realSprinklerSystem->turnOn();
}

void SprinklerSystemProxy::turnOff()
{
    _realSprinklerSystem->turnOff();
}

void SprinklerSystemProxy::schedule(QDateTime delay, int duration)
{
    _realSprinklerSystem->schedule(delay, duration);
}

void SprinklerSystemProxy::passRealSprinklerSystem(RealSprinklerSystem *realSprinklerSystem)
{
    _realSprinklerSystem = realSprinklerSystem;
}

void SprinklerSystemProxy::getDeviceInfo()
{
    _realSprinklerSystem->getDeviceInfo();
}