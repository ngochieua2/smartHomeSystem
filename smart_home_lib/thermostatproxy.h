#ifndef THERMOSTATPROXY_H
#define THERMOSTATPROXY_H

#include <thermostat.h>
#include <realthermostat.h>

class RealThermostat;

class ThermostatProxy : public Thermostat
{
public:
    ThermostatProxy();
    ThermostatProxy(QString id, QUrl Url);
    virtual ~ThermostatProxy();

    QString getID();

    void passRealThermostat(RealThermostat* realThermostat);

    void getDeviceInfo() override;

private:
    RealThermostat* _realThermostat{nullptr};

};

#endif // THERMOSTATPROXY_H
