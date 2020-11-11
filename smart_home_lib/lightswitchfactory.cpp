#include "lightswitchfactory.h"
#include "reallightswitch.h"

SmartHomeDevices *LightSwitchFactory::CreateDevice(QString id, QString type, QUrl url)
{
    return new RealLightSwitch(id, type, url);
}
