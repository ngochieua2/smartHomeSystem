#include "lightswitchproxy.h"

LightSwitchProxy::LightSwitchProxy()
{
}

LightSwitchProxy::LightSwitchProxy(QString id, QUrl Url)
{
    _device_id = id;
    _devideType = "lightSwitch";
    _deviceUrl = Url;
}

LightSwitchProxy::~LightSwitchProxy()
{
    delete _realLightSwitch;
}

QString LightSwitchProxy::getID()
{
    return _device_id;
}

void LightSwitchProxy::turnOn()
{
    _realLightSwitch->turnOn();
}

void LightSwitchProxy::turnOff()
{
    _realLightSwitch->turnOff();
}

void LightSwitchProxy::dim()
{
    _realLightSwitch->dim();
}

void LightSwitchProxy::brighten()
{
    _realLightSwitch->brighten();
}

void LightSwitchProxy::passRealLightSwitch(RealLightSwitch *realLightSwitch)
{
    _realLightSwitch = realLightSwitch;
}

void LightSwitchProxy::getDeviceInfo()
{
    _realLightSwitch->getDeviceInfo();
}

void LightSwitchProxy::getMeasurement()
{
    _realLightSwitch->getMeasurement();
}
