#include "smarthomecontroller.h"

SmartHomeController::SmartHomeController()
{

}

SmartHomeController::~SmartHomeController()
{
    delete _deviceInfoPointer;
}



void SmartHomeController::SmartHomeController::unregisterDevice()
{

}

QString SmartHomeController::configController(QString name, QUrl URL)
{
    return "Success";
}
