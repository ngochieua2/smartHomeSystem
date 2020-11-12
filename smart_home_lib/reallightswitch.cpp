#include "reallightswitch.h"

RealLightSwitch::RealLightSwitch(QString id, QUrl url)
{
    _Device_id = id;
    _Url = url;
}

void RealLightSwitch::turnOn()
{
    OnOffState = true;
}

void RealLightSwitch::turnOff()
{
    OnOffState = false;
}
void RealLightSwitch::dim()
{
    if (brightnessLevel > 20){
        brightnessLevel -= 20;
    }
}

void RealLightSwitch::brighten()
{
    if (brightnessLevel < 100){
        brightnessLevel += 20;
    }
    if (brightnessLevel > 100){
        brightnessLevel = 100;
    }
}


