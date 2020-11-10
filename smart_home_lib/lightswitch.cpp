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

void LightSwitch::turnOn()
{
    OnOffState = true;
}

void LightSwitch::turnOff()
{
    OnOffState = false;
}

void LightSwitch::dim()
{
    if (brightnessLevel > 20){
        brightnessLevel -= 20;
    }
}

void LightSwitch::brighten()
{
    if (brightnessLevel < 100){
        brightnessLevel += 20;
    }
    if (brightnessLevel > 100){
        brightnessLevel = 100;
    }
}
