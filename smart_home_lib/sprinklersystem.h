#ifndef SPRINKLERSYSTEM_H
#define SPRINKLERSYSTEM_H
#include <QTimer>
#include "smarthomedevice.h"

class SprinklerSystem : public SmartHomeDevice
{
public:
    SprinklerSystem();
    ~SprinklerSystem();
    /*!
     * @brief virtual turnOn will be overrided in concrete class
     */
    virtual void turnOn() = 0;
    /*!
     * @brief virtual turnOff will be overrided in concrete class
     */
    virtual void turnOff() = 0;
    /*!
     * @brief virtual schedule will be overrided in concrete class
     */
    virtual void schedule (int delay, int duration) = 0;
    /*!
     * @brief virtual getDeviceInfo will be overrided in concrete class
     */
    virtual void getDeviceInfo() = 0;
    /*!
     * @brief virtual getMeasurement will be overrided in concrete class
     */
    virtual void getMeasurement() = 0;
    /*!
     * @brief virtual getWaterUsage will be overrided in concrete class
     */
    virtual void getWaterUsage() = 0;
    /*!
     * @brief virtual updateTime will be overrided in concrete class
     */
    virtual void updateTime() = 0;
};

#endif // SPRINKLERSYSTEM_H
