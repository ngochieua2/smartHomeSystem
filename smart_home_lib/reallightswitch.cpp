#include "reallightswitch.h"

RealLightSwitch::RealLightSwitch()
{

}

RealLightSwitch::RealLightSwitch(QString id, QUrl URL)
{
    _device_id = id;
    _devideType = "light Switch";
    _deviceUrl = URL;
    _deviceInfo = new DeviceInfo(_device_id,_devideType,_deviceUrl);
}

RealLightSwitch::~RealLightSwitch()
{

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

void RealLightSwitch::createControllerProxy()
{
    _controllerProxy = new ControllerProxy();
}

ControllerProxy *RealLightSwitch::getControllerProxy()
{
    return _controllerProxy;
}

void RealLightSwitch::getDeviceInfo()
{
    _controllerProxy->receiveDeviceInfo(_deviceInfo);
    _deviceInfo = new DeviceInfo(_device_id,_devideType,_deviceUrl);
    _deviceInfo->updateTime();

}
