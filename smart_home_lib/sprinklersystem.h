#ifndef SPRINKLERSYSTEM_H
#define SPRINKLERSYSTEM_H

#include <smarthomedevices.h>

class SprinklerSystem: public SmartHomeDevices
{
public:
    SprinklerSystem();
    ~SprinklerSystem();


    virtual void turnOn() = 0;

    virtual void turnOff() = 0;

    virtual void schedule(int delay, int duration) = 0;

    // currentState : measurement

    //waterUsage : measurement

protected:
    bool OnOffStatus{};
    int updatedFrequency{5};
    double waterConsumption{};

};

#endif // SPRINKLERSYSTEM_H
