#ifndef LIGHTSWITCH_H
#define LIGHTSWITCH_H

#include <smarthomedevice.h>

class LightSwitch : public SmartHomeDevice
{
public:
    LightSwitch();
    ~LightSwitch();
    /*!
     * @brief virtual turnOn will be overrided in concrete class
     */
    virtual void turnOn() = 0;
    /*!
     * @brief virtual turnOff will be overrided in concrete class
     */
    virtual void turnOff() = 0;
    /*!
     * @brief virtual dim will be overrided in concrete class
     */
    virtual void dim() = 0;
    /*!
     * @brief virtual brighten will be overrided in concrete class
     */
    virtual void brighten() = 0;
    /*!
     * @brief virtual getDeviceInfo will be overrided in concrete class
     */
    virtual void getDeviceInfo() = 0;
    /*!
     * @brief virtual getMeasurement will be overrided in concrete class
     */
    virtual void getMeasurement() = 0;

};

#endif // LIGHTSWITCH_H
