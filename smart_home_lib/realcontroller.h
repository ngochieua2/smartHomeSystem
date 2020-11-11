#ifndef REALCONTROLLER_H
#define REALCONTROLLER_H
#include "controller.h"

class RealController : public Controller
{
public:
    RealController();
    RealController(QString id, QUrl url);
    virtual ~RealController();
    
    void registerDevice(QString name, QString type, QUrl url) override;
    void registeredDevices() override;
};

#endif // REALCONTROLLER_H
