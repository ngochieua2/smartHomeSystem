#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <smarthomedevice.h>

class Thermostat : public SmartHomeDevice
{
public:
    Thermostat();
    ~Thermostat();
    /*!
     * @brief virtual getLastMeasurement will be overrided in concrete class
     */
    virtual void getLastMeasurement() = 0;
    /*!
     * @brief virtual getLast5Measurement will be overrided in concrete class
     */
    virtual void getLast5Measurement() = 0;
    /*!
     * @brief virtual getSetPoint will be overrided in concrete class
     */
    virtual void getSetPoint() = 0;
    /*!
     * @brief virtual SetPoint will be overrided in concrete class
     */
    virtual void SetPoint(double setPoint) = 0;
    /*!
     * @brief virtual warmer will be overrided in concrete class
     */
    virtual void warmer(double amount) = 0;
    /*!
     * @brief virtual cooler will be overrided in concrete class
     */
    virtual void cooler(double amount) = 0;
    /*!
     * @brief virtual getDeviceInfo will be overrided in concrete class
     */
    virtual void getDeviceInfo() = 0;
    /*!
     * @brief virtual getMeasurement will be overrided in concrete class
     */
    virtual void getMeasurement() = 0;
    /*!
     * @brief virtual Update will be overrided in concrete class
     */
    virtual void Update() = 0;

};

#endif // THERMOSTAT_H
