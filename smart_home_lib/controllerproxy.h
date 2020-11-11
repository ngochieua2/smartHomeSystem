#ifndef CONTROLLERPROXY_H
#define CONTROLLERPROXY_H
#include "controller.h"
#include "realcontroller.h"

class ControllerProxy : public Controller
{
public:
    ControllerProxy(RealController* realController);
    ~ControllerProxy();
    ControllerProxy(QString id, QUrl url);
    void registerDevice(QString name, QString type, QUrl url) override;
    void registeredDevices() override;
private:
    RealController* _realController;
};

#endif // CONTROLLERPROXY_H
