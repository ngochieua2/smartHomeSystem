#ifndef REALCONTROLLER_H
#define REALCONTROLLER_H

#include <smarthomecontroller.h>
#include <lightswitchproxy.h>
#include <thermostatproxy.h>

class LightSwitchProxy;
class ThermostatProxy;

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

    ThermostatProxy* getThermostatProxy();

    QList<ThermostatProxy*> getThermostatProxyList();

    void receiveDeviceInfo(DeviceInfo *deviceInfo) override;

    QList<DeviceInfo*> getDeviceInfoList();


private:
    QList <LightSwitchProxy*> _lightSwitchProxyList{};
    QList <ThermostatProxy*> _thermostatProxyList{};

    QList<DeviceInfo*> _deviceInfoList{};

};

#endif // REALCONTROLLER_H
