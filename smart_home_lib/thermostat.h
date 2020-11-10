#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <smarthomedevices.h>

class Thermostat : public SmartHomeDevices
{
public:
    Thermostat();
    ~Thermostat();

    //LastMeasurement()

    //last5Measurement()

    double setpoint(double desiredTemp);

    //currentState;

    void warmer( double amount);

    void cooler(double amount);

protected:
    int updateFrequency{3};
    double currentTemp{};
    double lastTemp{};
};

#endif // THERMOSTAT_H
