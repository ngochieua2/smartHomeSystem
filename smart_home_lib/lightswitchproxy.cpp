#include "lightswitchproxy.h"

LightSwitchProxy::LightSwitchProxy(RealLightSwitch *realLight)
{
    _realLight = realLight;
}

LightSwitchProxy::~LightSwitchProxy()
{
    delete _realLight;
    delete  _factory;
}




