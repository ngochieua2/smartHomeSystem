#ifndef SMARTHOMECONTROLLER_H
#define SMARTHOMECONTROLLER_H

#include <QString>
#include <QUrl>
#include <deviceinfo.h>
#include <measurement.h>

class SmartHomeController
{
public:
    SmartHomeController();
    ~SmartHomeController();

    //virtual void registerDevice(QString name,QString type, QUrl URL) = 0;

    virtual void receiveDeviceInfo(DeviceInfo* deviceInfo) = 0;

    virtual void report(QList <Measurement*> measurementList) = 0;

protected:
    QString _controller_id{};
    QUrl _controller_Url{};


};

#endif // SMARTHOMECONTROLLER_H
