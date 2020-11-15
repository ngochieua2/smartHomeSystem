#ifndef SPRINKLERSYSTEM_H
#define SPRINKLERSYSTEM_H
#include <QTimer>
#include "smarthomedevice.h"

class SprinklerSystem : public SmartHomeDevice
{
public:
    SprinklerSystem();
    ~SprinklerSystem();

    virtual void turnOn() = 0;

    virtual void turnOff() = 0;

    virtual void schedule (int delay, int duration) = 0;

    virtual void getDeviceInfo() = 0;

    virtual void getMeasurement() = 0;

    virtual void getWaterUsage() = 0;
    
    virtual void updateTime() = 0;
};

#endif // SPRINKLERSYSTEM_H
