#ifndef SPRINKLERSYSTEMFACTORY_H
#define SPRINKLERSYSTEMFACTORY_H
#include "devicefactory.h"
#include "smarthomedevice.h"
#include "realsprinklersystem.h"

class SprinklerSystemFactory : public DeviceFactory
{
public:
    /*!
     * @brief CreateDevice will creat a new device with given name and url
     * in this class the created device will be a RealSprinklerSystem
     * @param name
     * @param url
     * @return RealSprinklerSystem
     */
    SmartHomeDevice* CreateDevice(QString id, QUrl url) override;
};

#endif // SPRINKLERSYSTEMFACTORY_H
