#ifndef CONTROLLERPROXY_H
#define CONTROLLERPROXY_H
#include "smarthomecontroller.h"
#include "realcontroller.h"
class RealController;
class RealLightSwitch;
class ControllerProxy : public SmartHomeController
{
public:
    ControllerProxy(RealController* realController);
    virtual ~ControllerProxy();
    ControllerProxy(QString id, QUrl url);
    void registerDevice(QString id, QString type, QUrl url) override;
    void registeredDevices() override;
    void unregisterDevice(QString id) override;
    QString configController(QString id, QUrl URL) override;
private:
    RealController* _realController;
};

#endif // CONTROLLERPROXY_H
