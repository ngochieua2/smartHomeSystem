#include "controllerproxy.h"

ControllerProxy::ControllerProxy()
{

}

ControllerProxy::~ControllerProxy()
{

}

void ControllerProxy::passController(RealController *controller)
{
    _realController = controller;
}

void ControllerProxy::receiveDeviceInfo(DeviceInfo *deviceInfo)
{
    _realController->receiveDeviceInfo(deviceInfo);
}
