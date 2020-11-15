#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H
#include <QString>
#include <QUrl>
#include "smarthomedevice.h"

class DeviceFactory
{
public:
    /*!
     * @brief CreateDevice will creat a new device with given name and url
     * this function will be implemented in its derived classes.
     * @param name
     * @param url
     * @return AbstractDevice
     */
    virtual SmartHomeDevice* CreateDevice(QString id, QUrl url) = 0;
};

#endif // DEVICEFACTORY_H
