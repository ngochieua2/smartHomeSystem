#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H
#include "smarthomedevices.h"

class DeviceFactory
{
public:
    /**
     * @brief CreateDevice will creat a new device with given name and url
     * this function will be implemented in its derived classes.
     * @param name
     * @param url
     * @return AbstractDevice 
     */
    virtual SmartHomeDevices* CreateDevice(QString name, QUrl url) = 0;
};

#endif // DEVICEFACTORY_H
