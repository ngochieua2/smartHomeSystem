#ifndef REALCONTROLLER_H
#define REALCONTROLLER_H
#include "smarthomecontroller.h"

class RealController : public SmartHomeController
{
public:
    RealController();
    RealController(QString id, QUrl url);
    virtual ~RealController();
    
    void registerDevice(QString name, QString type, QUrl url) override;
    void registeredDevices() override;
    void unregisterDevice() override;
    QString configController(QString name, QUrl URL) override;
};

#endif // REALCONTROLLER_H
