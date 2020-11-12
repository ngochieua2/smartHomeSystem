#include "lightswitch.h"

LightSwitch::LightSwitch()
{
}

LightSwitch::LightSwitch(QString id, QUrl Url)
{
    _Device_id = id;
    _devideType = "LightSwitch";
    _Url = Url;
}

LightSwitch::~LightSwitch()
{
}
