#include "sprinklersystemproxy.h"

SprinklerSystemProxy::SprinklerSystemProxy(RealSprinklerSysem *realSprinkler)
{
    _realSprinkler = realSprinkler;
}
SprinklerSystemProxy::~SprinklerSystemProxy(){
    delete _realSprinkler;
}

void SprinklerSystemProxy::turnOn()
{
    this->_realSprinkler->turnOn();
}

void SprinklerSystemProxy::turnOff()
{
    this->_realSprinkler->turnOff();
}

void SprinklerSystemProxy::schedule(int delay, int duration)
{
    this->_realSprinkler->schedule(delay, duration);
}

//void SprinklerSystemProxy::setControllerProxy(ControllerProxy *controllerProxy)
//{
//    this->_realSprinkler->setControllerProxy(controllerProxy);
//}
