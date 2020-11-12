#include "smarthomecontroller.h"

SmartHomeController::SmartHomeController()
{
    
}

SmartHomeController::SmartHomeController(QString id, QUrl url)
{
    _controller_id = id;
    _controller_Url = url;
}

SmartHomeController::~SmartHomeController()
{
    delete _deviceInfoPointer;
}




