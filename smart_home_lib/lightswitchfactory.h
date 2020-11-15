#ifndef LIGHTSWITCHFACTORY_H
#define LIGHTSWITCHFACTORY_H

#include "devicefactory.h"
#include "smarthomedevice.h"
#include "reallightswitch.h"

class LightSwitchFactory : public DeviceFactory
{
public:
    /*!
     * @brief CreateDevice will creat a new device with given name and url
     * in this class the created device will be a RealLightSwitch
     * @param name
     * @param url
     * @return RealLightSwitch
     */
    SmartHomeDevice* CreateDevice(QString id, QUrl url) override;
};

#endif // LIGHTSWITCHFACTORY_H
