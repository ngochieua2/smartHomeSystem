#include "thermostatproxy.h"

ThermostatProxy::ThermostatProxy()
{
}

ThermostatProxy::ThermostatProxy(QString id, QUrl Url)
{
    _device_id = id;
    _devideType = "lightSwitch";
    _deviceUrl = Url;
}

ThermostatProxy::~ThermostatProxy()
{
    delete _realThermostat;
}

QString ThermostatProxy::getID()
{
    return _device_id;
}

void ThermostatProxy::passRealThermostat(RealThermostat *realThermostat)
{
    _realThermostat = realThermostat;
}

void ThermostatProxy::getDeviceInfo()
{
    _realThermostat->getDeviceInfo();
}
