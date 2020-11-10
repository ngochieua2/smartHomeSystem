#ifndef SMARTHOMECONTROLLER_H
#define SMARTHOMECONTROLLER_H

#include <QString>
#include <QUrl>
#include <QList>
#include <deviceinfo.h>

class SmartHomeController
{
public:
    SmartHomeController();
    ~SmartHomeController();

    virtual void registerDevice(QString name,QString type, QUrl URL) = 0;

    // registedDevices();

    virtual void unregisterDevice();

    //void report(measurement);

    // currentState();

    //void addfilter(QString deviceName, measurementType, filterType, configuration);

    //void clearFilter(QString deviceName, measurementType);

    QString configController(QString name, QUrl URL);


protected:
    QString _controller_id{};
    QUrl _controller_Url{};

    //measurement



    DeviceInfo* _deviceInfoPointer{nullptr};
};

#endif // SMARTHOMECONTROLLER_H
