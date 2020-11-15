#ifndef SMARTHOMECONTROLLER_H
#define SMARTHOMECONTROLLER_H

#include <QString>
#include <QUrl>
#include <QList>
#include <QtNetwork>
#include <QDebug>
#include "deviceinfo.h"
#include <measurement.h>

class SmartHomeController
{
public:
    SmartHomeController();
    SmartHomeController(QString id,QString url);
    ~SmartHomeController();

    void registerDevice(QString name,QString type,QUrl URL);

    QString registerdDevices();

    bool unregisterDevice(QString name);

    QStringList currentState(QString name = "", QString type = "");

    void addFilter(QString deviceName,int measurementType,int filterType,QString configuration);

    void clearFilter(QString deviceName,int measurementType);

    virtual void receiveDeviceInfo(DeviceInfo *deviceInfo) = 0;

    virtual void report(QList<Measurement *> measurementList) = 0;

private:

    QString m_id{};
    QString m_name{};
    QString m_url{};
    QString m_ip{};
    QString m_port{};

    QList<DeviceInfo*> m_deviceInfoList;

protected:

    QString _controller_id{};
    QUrl _controller_Url{};

};


#endif // SMARTHOMECONTROLLER_H
