#include "realthermostat.h"

RealThermostat::RealThermostat()
{

}

RealThermostat::RealThermostat(QString id, QUrl URL)
{
    _device_id = id;
    _devideType = "Thermostat";
    _deviceUrl = URL;
    _deviceInfo = new DeviceInfo(_device_id, _devideType, _deviceUrl);

    //set default value
    _lastPoint = 18.00;
    _currentPoint = 18.00;
    _state = 0;
}

RealThermostat::~RealThermostat()
{
    delete _deviceInfo;
    delete _controllerProxy;
}

void RealThermostat::createControllerProxy()
{
    _controllerProxy = new ControllerProxy();
}

ControllerProxy *RealThermostat::getControllerProxy()
{
    return _controllerProxy;
}

void RealThermostat::getDeviceInfo()
{
    _controllerProxy->receiveDeviceInfo(_deviceInfo);
    _deviceInfo = new DeviceInfo(_device_id,_devideType,_deviceUrl);
    _deviceInfo->updateTime();
}

void RealThermostat::updateMeasurement()
{
    _mesurementList.clear();
    _measurement = new Measurement(_device_id, Measurement::measurementType::thermostatState, _state);
    _mesurementList.append(_measurement);

}

QList<Measurement *> RealThermostat::currentState()
{
    return _mesurementList;
}

void RealThermostat::getMeasurement()
{
    updateMeasurement();
    _controllerProxy->report(currentState());
}
