#ifndef THERMOSTATFACTORY_H
#define THERMOSTATFACTORY_H
#include "devicefactory.h"
#include "realthermostat.h"
class ThermostatFactory : public DeviceFactory
{
public:
    /**
     * @brief CreateDevice will creat a new device with given name and url
     * in this class the created device will be a RealThermostat
     * @param name
     * @param url
     * @return RealThermostat 
     */
    SmartHomeDevices * CreateDevice(QString id, QUrl url) override;
};

#endif // THERMOSTATFACTORY_H
