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
    double setpoint(double desiredTemp) override;
    void warmer(double amount) override;
    void cooler(double amount) override;
private:
    RealThermostat* _realThermostat{};
};

#endif // THERMOSTATPROXY_H