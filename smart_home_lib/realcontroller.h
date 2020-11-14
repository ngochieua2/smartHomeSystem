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
    
    void report(QList<Measurement *> measurementList) override;
private:
    //light proxy
    QList <LightSwitchProxy*> _lightSwitchProxyList{};

    QList<DeviceInfo*> _deviceInfoList{};
    
    QList<Measurement*> _measurementList{};
    

};

#endif // REALCONTROLLER_H
