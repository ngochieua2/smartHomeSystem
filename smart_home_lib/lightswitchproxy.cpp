#include "lightswitchproxy.h"

void LightSwitchProxy::setRealLight(RealLightSwitch* realLight)
{
    _realLight = realLight;
}

LightSwitchProxy::~LightSwitchProxy()
{
    delete _realLight;
}

void LightSwitchProxy::turnOn()
{
    this->_realLight->turnOn();
}

void LightSwitchProxy::turnOff()
{
    this->_realLight->turnOff();
}

void LightSwitchProxy::dim()
{
    this->_realLight->dim();
}

void LightSwitchProxy::brighten()
{
    this->_realLight->brighten();
}





//void LightSwitchProxy::setControllerProxy(ControllerProxy *controllerProxy)
//{
  //  this->_realLight->setControllerProxy(controllerProxy);
//}




