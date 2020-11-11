#ifndef LIGHTSWITTCHFACTORY_H
#define LIGHTSWITTCHFACTORY_H
#include "devicefactory.h"

class LightSwittchFactory : public DeviceFactory
{
public:
    /**
     * @brief CreateDevice will creat a new device with given name and url
     * in this class the created device will be a RealLightSwitch
     * @param name
     * @param url
     * @return RealLightSwitch 
     */
    SmartHomeDevices * CreateDevice(QString id, QString type, QUrl url) override;
};

#endif // LIGHTSWITTCHFACTORY_H
