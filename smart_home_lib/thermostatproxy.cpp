#include "thermostatproxy.h"

ThermostatProxy::ThermostatProxy(RealThermostat *realThermostat)
{
    _realThermostat = realThermostat;
}

ThermostatProxy::~ThermostatProxy()
{
    delete _realThermostat;
    delete  _factory;
}
