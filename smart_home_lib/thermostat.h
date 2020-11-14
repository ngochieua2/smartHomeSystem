#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <smarthomedevice.h>

class Thermostat : public SmartHomeDevice
{
public:
    Thermostat();
    ~Thermostat();

    virtual void getLastMeasurement() = 0;

    virtual void getLast5Measurement() = 0;

    virtual void SetPoint(double setPoint) = 0;

    virtual void warmer(double amount) = 0;

    virtual void cooler(double amount) = 0;

    virtual void getDeviceInfo() = 0;

    virtual void getMeasurement() = 0;

    virtual void Update() = 0;


};

#endif // THERMOSTAT_H
