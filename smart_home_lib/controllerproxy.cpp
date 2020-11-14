#include "controllerproxy.h"

ControllerProxy::ControllerProxy()
{
}

ControllerProxy::~ControllerProxy()
{
    delete _realController;
}

void ControllerProxy::passController(RealController *controller)
{
    _realController = controller;
}

void ControllerProxy::receiveDeviceInfo(DeviceInfo *deviceInfo)
{
    _realController->receiveDeviceInfo(deviceInfo);
}

void ControllerProxy::report(QList<Measurement *> measurementList)
{
    _realController->report(measurementList);
}

