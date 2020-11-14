#ifndef SMARTHOMECONTROLLER_H
#define SMARTHOMECONTROLLER_H

#include <QString>
#include <QUrl>
#include <QList>
#include <QtNetwork>
#include <QDebug>
#include "deviceinfo.h"


////智能家居控制器接收来自传感器/设备的测量值，并可以向设备发送查询和命令。

class SmartHomeController
{
public:
    SmartHomeController();
    SmartHomeController(QString id,QString url);
    ~SmartHomeController();

    void MenuInterface()
    {

    }

    void registerDevice(QString name,QString type,QUrl URL);

    QString registerdDevices();

    bool unregisterDevice(QString name);

    QStringList currentState(QString name = "", QString type = "");

    void addFilter(QString deviceName,int measurementType,int filterType,QString configuration)
    {

    }
    void clearFilter(QString deviceName,int measurementType)
    {

    }

private:

    void report(){}

private:

    QString m_id{};
    QString m_name{};
    QString m_url{};
    QString m_ip{};
    QString m_port{};

    QList<DeviceInfo*> m_deviceInfoList;

};


#endif // SMARTHOMECONTROLLER_H
