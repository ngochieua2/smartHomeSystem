#include "controllerproxy.h"

ControllerProxy::ControllerProxy(RealController *realController)
{
    
}

ControllerProxy::~ControllerProxy()
{
    delete _realController;
}

ControllerProxy::ControllerProxy(QString id, QUrl url)
{
    
}

void ControllerProxy::registerDevice(QString name, QString type, QUrl url)
{
    this->_realController->registerDevice(name,type,url);
}

void ControllerProxy::registeredDevices()
{
    this->_realController->registeredDevices();
}
