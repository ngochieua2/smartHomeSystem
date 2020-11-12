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

    virtual double setpoint(double desiredTemp) = 0;

    //currentState;

    virtual void warmer( double amount) = 0;

    virtual void cooler(double amount) = 0;
    
   //virtual void setControllerProxy(ControllerProxy *controllerProxy) override = 0;

protected:
    int updateFrequency{3};
    double currentTemp{};
    double lastTemp{};
};

#endif // THERMOSTAT_H
