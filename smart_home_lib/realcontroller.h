#ifndef REALCONTROLLER_H
#define REALCONTROLLER_H

#include <smarthomecontroller.h>
#include <lightswitchproxy.h>
#include <thermostatproxy.h>
#include <sprinklersystemproxy.h>

class LightSwitchProxy;
class ThermostatProxy;
class SprinklerSystemProxy;

class RealController : SmartHomeController
{
public:
    RealController();
    RealController(QString id, QUrl Url);
    virtual ~RealController();

    QString getID();

    void registerDevice(QString name, QString type, QUrl URL);

    QString registerDevice();

    void unregisterDevice(QString name);

    LightSwitchProxy* getLightSwitchProxy();

    QList<LightSwitchProxy*> getLightSwitchProxyList();

    ThermostatProxy* getThermostatProxy();

    QList<ThermostatProxy*> getThermostatProxyList();

    SprinklerSystemProxy* getSprinklerSystemProxy();

    QList<SprinklerSystemProxy*> getSprinklerSystemProxyList();

    void receiveDeviceInfo(DeviceInfo *deviceInfo) override;

    void report(QList<Measurement *> measurementList) override;

    QString currentState(QString name, QString Type);

    QString getUpdateMeasurement();

private:
    QList <LightSwitchProxy*> _lightSwitchProxyList{};
    QList <ThermostatProxy*> _thermostatProxyList{};
    QList <SprinklerSystemProxy*> _sprinklerSystemProxyList{};

    QList<DeviceInfo*> _deviceInfoList{};

    QList<Measurement*> _measurementList{};

};

#endif // REALCONTROLLER_H
