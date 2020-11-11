#include "realcontroller.h"

RealController::RealController()
{
    
}

void RealController::registerDevice(QString name, QString type, QUrl url)
{
    if (type == "LightSwitch") {
     RealLightSwitch realLight(name, url); 
     LightSwitchProxy lightSwitchProxy(&realLight);
     _lightSwitchProxy.push_back(&lightSwitchProxy);
    }
    if(type == "Thermostat"){
        
    }
}

void RealController::registeredDevices()
{
    for(int unsigned i = 0; i < _lightSwitchProxy.size(); i++){
        _lightSwitchProxy[i];
    }
    
}
