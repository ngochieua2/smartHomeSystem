#ifndef LIGHTSWITCH_H
#define LIGHTSWITCH_H

#include <smarthomedevice.h>

class LightSwitch : public SmartHomeDevice
{
public:
    LightSwitch();
    ~LightSwitch();

    virtual void turnOn() = 0;

    virtual void turnOff() = 0;

    virtual void dim() = 0;

    virtual void brighten() = 0;

    virtual void getDeviceInfo() = 0;

    virtual void getMeasurement() = 0;


};

#endif // LIGHTSWITCH_H
