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

    // Save default value
    _measurement = new Measurement(_device_id, Measurement::measurementType::lightSwitchOnOff, OnOffState);
    _measurementRecord.append(_measurement);
    _measurement = new Measurement(_device_id, Measurement::measurementType::brightnessLevel, brightnessLevel);
    _measurementRecord.append(_measurement);

}

RealLightSwitch::~RealLightSwitch()
{
    delete _deviceInfo;
    delete _controllerProxy;
    delete _measurement;
    for(int i = 0; i < _mesurementList.size(); i++){
        delete _mesurementList.at(i);
    }
    for(int i = 0; i < _measurementRecord.size(); i++){
        delete _measurementRecord.at(i);
    }
}

void RealLightSwitch::turnOn()
{
    OnOffState = true;
    _measurement = new Measurement(_device_id, Measurement::measurementType::lightSwitchOnOff, OnOffState);
    _measurementRecord.append(_measurement);
    if(!isSameValue()){
        getMeasurement();
    }
}

void RealLightSwitch::turnOff()
{
    OnOffState = false;
    _measurement = new Measurement(_device_id, Measurement::measurementType::lightSwitchOnOff, OnOffState);
    _measurementRecord.append(_measurement);
    if(!isSameValue()){
        getMeasurement();
    }
}

void RealLightSwitch::dim()
{
    if (brightnessLevel > 20){
        brightnessLevel -= 20;
    }
    _measurement = new Measurement(_device_id, Measurement::measurementType::brightnessLevel, brightnessLevel);
    _measurementRecord.append(_measurement);
    if(!isSameValue()){
        getMeasurement();
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
    _measurement = new Measurement(_device_id, Measurement::measurementType::brightnessLevel, brightnessLevel);
    _measurementRecord.append(_measurement);
    if(!isSameValue()){
        getMeasurement();
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

QList<Measurement *> RealLightSwitch::currentState()
{
    _mesurementList.clear();
    //create measurement 1
    _measurement = new Measurement(_device_id, Measurement::measurementType::lightSwitchOnOff, OnOffState);
    _mesurementList.append(_measurement);
    //Create measurement 2
    _measurement = new Measurement(_device_id, Measurement::measurementType::brightnessLevel, brightnessLevel);
    _mesurementList.append(_measurement);

    return _mesurementList;
}

void RealLightSwitch::getMeasurement()
{
    _controllerProxy->report(currentState());
}

bool RealLightSwitch::isSameValue()
{
    for (int i = _measurementRecord.size() - 2; i >= 0; i--){
        if(_measurementRecord.last()->getType() == _measurementRecord.at(i)->getType()){
            if(_measurementRecord.last()->value() == _measurementRecord.at(i)->value()){
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

