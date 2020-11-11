#include "lightswitchproxy.h"


LightSwitchProxy::LightSwitchProxy(RealLightSwitch *realLight)
{
    _realLight = realLight;
}
LightSwitchProxy::LightSwitchProxy(QString id, QString type, QUrl url){

    _Device_id = id;
    _devideType = type;
    _Url = url;
}
