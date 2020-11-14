#include "reallightswitch.h"

RealLightSwitch::RealLightSwitch()
{

}

RealLightSwitch::RealLightSwitch(QString id, QUrl URL)
{
    _device_id = id;
    _devideType = "Light Switch";
    _deviceUrl = URL;
    _deviceInfo = new DeviceInfo(_device_id,_devideType,_deviceUrl);

    //set value default
    OnOffState = true;
    brightnessLevel = 50;

    updateMeasurement();
}

RealLightSwitch::~RealLightSwitch()
{
    delete _deviceInfo;
    delete _controllerProxy;
    delete _measurement;
    for(int i = 0; i < _mesurementList.size(); i++){
        delete _mesurementList.at(i);
    }
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

void RealLightSwitch::updateMeasurement()
{
    _mesurementList.clear();
    //create measurement 1
    _measurement = new Measurement(_device_id, Measurement::measurementType::lightSwitchOnOff, OnOffState);
    _mesurementList.append(_measurement);
    //Create measurement 2
    _measurement = new Measurement(_device_id, Measurement::measurementType::brightnessLevel, brightnessLevel);
    _mesurementList.append(_measurement);
}

QList<Measurement *> RealLightSwitch::currentState()
{
    return _mesurementList;
}

void RealLightSwitch::getMeasurement()
{
    updateMeasurement();
    _controllerProxy->report(currentState());
}
