#ifndef THERMOSTATPROXY_H
#define THERMOSTATPROXY_H
#include "thermostatfactory.h"
#include "thermostat.h"
#include "realthermostat.h"

class ThermostatProxy : public Thermostat
{
public:
    ThermostatProxy(RealThermostat* realThermostat);
    ~ThermostatProxy();
private:
    RealThermostat* _realThermostat{};
    ThermostatFactory* _factory{};
};

#endif // THERMOSTATPROXY_H
