#ifndef REALTHERMOSTAT_H
#define REALTHERMOSTAT_H
#include "thermostat.h"

class RealThermostat : public Thermostat
{
public:
    RealThermostat(QString id, QUrl url);
    virtual ~RealThermostat();
    double setpoint(double desiredTemp) override;
    void warmer(double amount) override;
    void cooler(double amount) override;
    //void setControllerProxy(ControllerProxy *controllerProxy) override;
};

#endif // REALTHERMOSTAT_H
