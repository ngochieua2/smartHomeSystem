#ifndef SMARTHOMEDEVICES_H
#define SMARTHOMEDEVICES_H

#include <QString>
#include <QUrl>

class SmartHomeDevices
{
public:
    SmartHomeDevices();
    ~SmartHomeDevices();


protected:
    QString _Device_id{};
    QString _devideType{};
    QUrl _Url{};
};

#endif // SMARTHOMEDEVICES_H
