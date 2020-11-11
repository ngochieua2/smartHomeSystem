#include "thermostatproxy.h"

ThermostatProxy::ThermostatProxy(RealThermostat *realThermostat)
{
    _realThermostat = realThermostat;
}

ThermostatProxy::~ThermostatProxy()
{
    delete _realThermostat;
}

double ThermostatProxy::setpoint(double desiredTemp)
{
   return this->_realThermostat->setpoint(desiredTemp);
}

void ThermostatProxy::warmer(double amount)
{
    this->_realThermostat->warmer(amount);
}

void ThermostatProxy::cooler(double amount)
{
    this->_realThermostat->cooler(amount);
}
