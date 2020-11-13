#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <smarthomedevice.h>

class Thermostat : public SmartHomeDevice
{
public:
    Thermostat();
    ~Thermostat();

    //LastMeasurement
    //Last4Measurement
    //SetPoint();
    //currentState
    //warmer
    //cooler

    virtual void getDeviceInfo() = 0;


};

#endif // THERMOSTAT_H
