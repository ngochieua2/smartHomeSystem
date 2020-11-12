#ifndef REALCONTROLLER_H
#define REALCONTROLLER_H
#include "smarthomecontroller.h"
#include "lightswitchproxy.h"

class ControllerProxy;
class RealController : public SmartHomeController
{
public:
    RealController();
    RealController(QString id, QUrl url);
    virtual ~RealController();
    
    void registerDevice(QString id, QString type, QUrl url) override;
    void registeredDevices() override;
    void unregisterDevice(QString id) override;
    QString configController(QString id, QUrl URL) override;
};

#endif // REALCONTROLLER_H
