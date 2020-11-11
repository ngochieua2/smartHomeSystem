#ifndef CONTROLLERPROXY_H
#define CONTROLLERPROXY_H
#include "smarthomecontroller.h"
#include "realcontroller.h"

class ControllerProxy : public SmartHomeController
{
public:
    ControllerProxy(RealController* realController);
    ~ControllerProxy();
    ControllerProxy(QString id, QUrl url);
    void registerDevice(QString name, QString type, QUrl url) override;
    void registeredDevices() override;
    void unregisterDevice() override;
    QString configController(QString name, QUrl URL) override;
private:
    RealController* _realController;
};

#endif // CONTROLLERPROXY_H
