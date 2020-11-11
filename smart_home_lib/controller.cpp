#include "controller.h"

Controller::Controller()
{
    
}

Controller::Controller(QString id, QUrl url)
{
    _id = id;
    _url = url;
}

void Controller::registerDevice(QString name, QString type, QUrl url)
{
   if (type == "LightSwitch") {
    RealLightSwitch realLight(name, url); 
    LightSwitchProxy lightSwitchProxy(&realLight);
    _lightSwitchProxy.push_back(&lightSwitchProxy);
   }
}

void Controller::registeredDevices()
{
    for(int unsigned i = 0; i < _lightSwitchProxy.size(); i++){
        _lightSwitchProxy[i];
    }
}
