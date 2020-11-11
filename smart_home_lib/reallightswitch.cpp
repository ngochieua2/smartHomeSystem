#include "reallightswitch.h"

RealLightSwitch::RealLightSwitch()
{
    
}

RealLightSwitch::RealLightSwitch(QString deviceId, QString deviceType, QUrl url)
{
    _Device_id = deviceId;
    _devideType = deviceType;
    _Url = url;
}

