#ifndef CONTROLLERPROXY_H
#define CONTROLLERPROXY_H

#include <smarthomecontroller.h>
#include <realcontroller.h>

class RealController;

class ControllerProxy : public SmartHomeController
{
public:
    ControllerProxy();
    virtual ~ControllerProxy();

    void passController(RealController* controller);

    void receiveDeviceInfo(DeviceInfo *deviceInfo) override;

private:
    RealController* _realController{nullptr};
};

#endif // CONTROLLERPROXY_H
