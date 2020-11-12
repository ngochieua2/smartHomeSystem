#include "controllerproxy.h"

ControllerProxy::ControllerProxy(RealController *realController)
{
    _realController = realController;
}

ControllerProxy::~ControllerProxy()
{
    delete _realController;
}

void ControllerProxy::registerDevice(QString name, QString type, QUrl url)
{
    this->_realController->registerDevice(name,type,url);
}

void ControllerProxy::registeredDevices()
{
    this->_realController->registeredDevices();
}

void ControllerProxy::unregisterDevice(QString name)
{
    this->_realController->unregisterDevice(name);
}

QString ControllerProxy::configController(QString name, QUrl URL)
{
   return this->_realController->configController(name,URL);
}
