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
