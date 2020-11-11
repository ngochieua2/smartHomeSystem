#include "lightswitchfactory.h"
#include "reallightswitch.h"

SmartHomeDevices *LightSwitchFactory::CreateDevice(QString id, QUrl url)
{
    return new RealLightSwitch(id, url);
}
