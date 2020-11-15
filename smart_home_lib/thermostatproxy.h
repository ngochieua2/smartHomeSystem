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

    void getLastMeasurement() override;

    void getLast5Measurement() override;

    void getSetPoint() override;

    void SetPoint(double setPoint) override;

    void warmer(double amount) override;

    void cooler(double amount) override;

    void passRealThermostat(RealThermostat* realThermostat);

    void getDeviceInfo() override;

    void getMeasurement() override;

    void Update() override;

private:
    RealThermostat* _realThermostat{nullptr};

};

#endif // THERMOSTATPROXY_H
