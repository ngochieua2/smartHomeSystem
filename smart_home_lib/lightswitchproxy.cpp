#include "lightswitchproxy.h"

LightSwitchProxy::LightSwitchProxy()
{
    
}
LightSwitchProxy::LightSwitchProxy(QString id, QString type, QUrl url){

    _Device_id = id;
    _devideType = type;
    _Url = url;
}
