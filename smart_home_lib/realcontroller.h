#ifndef REALCONTROLLER_H
#define REALCONTROLLER_H

#include <smarthomecontroller.h>
#include <lightswitchproxy.h>

class LightSwitchProxy;

class RealController : SmartHomeController
{
public:
    RealController();
    RealController(QString id, QUrl Url);
    ~RealController();

    QString getID();

    void registerDevice(QString name, QString type, QUrl URL);

    QString registerDevice();

    LightSwitchProxy* getLightSwitchProxy();

    QList<LightSwitchProxy*> getLightSwitchProxyList();

    void receiveDeviceInfo(DeviceInfo *deviceInfo) override;

    QList<DeviceInfo*> getDeviceInfoList();


private:
    //light proxy
    QList <LightSwitchProxy*> _lightSwitchProxyList{};

    QList<DeviceInfo*> _deviceInfoList{};

};

#endif // REALCONTROLLER_H
