#include "lightswittchfactory.h"
#include "reallightswitch.h"

SmartHomeDevices *LightSwittchFactory::CreateDevice(QString id, QString type, QUrl url)
{
    return new RealLightSwitch(id, type, url);
}
