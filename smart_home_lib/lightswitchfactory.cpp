#include "lightswitchfactory.h"

SmartHomeDevice *LightSwitchFactory::CreateDevice(QString id, QUrl url)
{
    return new RealLightSwitch(id, url);    
}
