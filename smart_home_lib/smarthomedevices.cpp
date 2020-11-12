#include "smarthomedevices.h"

SmartHomeDevices::SmartHomeDevices()
{
}

SmartHomeDevices::~SmartHomeDevices()
{
    delete _controllerProxy;
    
}

void SmartHomeDevices::setControllerProxy(ControllerProxy *controllerProxy){
    _controllerProxy = controllerProxy;
}

QString SmartHomeDevices::getId()
{
    return _Device_id;
}
