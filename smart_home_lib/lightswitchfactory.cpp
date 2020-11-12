#include "reallightswitch.h"
#include "lightswitchfactory.h"

SmartHomeDevices *LightSwitchFactory::CreateDevice(QString id, QUrl url)
{
    return new RealLightSwitch(id, url);
}
