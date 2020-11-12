#ifndef SPRINKLERSYSTEMFACTORY_H
#define SPRINKLERSYSTEMFACTORY_H
#include "realsprinklersysem.h"
#include "devicefactory.h"

class SprinklerSystemFactory : public DeviceFactory
{

public:
    /**
     * @brief CreateDevice will creat a new device with given name and url
     * in this class the created device will be a RealLightSwitch
     * @param name
     * @param url
     * @return RealLightSwitch 
     */
    SmartHomeDevices * CreateDevice(QString id, QUrl url) override;
};

#endif // SPRINKLERSYSTEMFACTORY_H
