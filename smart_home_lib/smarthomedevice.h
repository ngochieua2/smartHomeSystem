#ifndef SMARTHOMEDEVICE_H
#define SMARTHOMEDEVICE_H

#include <QString>
#include <QUrl>
#include <deviceinfo.h>
#include "measurement.h"

class SmartHomeDevice
{
public:
    SmartHomeDevice();
    ~SmartHomeDevice();

protected:
    QString _device_id{};
    QString _devideType{};
    QUrl _deviceUrl{};
};

#endif // SMARTHOMEDEVICE_H
