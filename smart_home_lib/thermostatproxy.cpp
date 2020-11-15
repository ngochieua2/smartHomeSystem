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

void ThermostatProxy::getLastMeasurement()
{
    _realThermostat->getLastMeasurement();
}

void ThermostatProxy::getLast5Measurement()
{
    _realThermostat->getLast5Measurement();
}

void ThermostatProxy::getSetPoint()
{
    _realThermostat->getSetPoint();
}

void ThermostatProxy::SetPoint(double setPoint)
{
    _realThermostat->SetPoint(setPoint);
}

void ThermostatProxy::warmer(double amount)
{
    _realThermostat->warmer(amount);
}

void ThermostatProxy::cooler(double amount)
{
    _realThermostat->cooler(amount);
}

void ThermostatProxy::passRealThermostat(RealThermostat *realThermostat)
{
    _realThermostat = realThermostat;
}

void ThermostatProxy::getDeviceInfo()
{
    _realThermostat->getDeviceInfo();
}

void ThermostatProxy::getMeasurement()
{
    _realThermostat->getMeasurement();
}

void ThermostatProxy::Update()
{
    _realThermostat->Update();
}
