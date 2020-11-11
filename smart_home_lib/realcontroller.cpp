#include "realcontroller.h"

void RealController::registerDevice(QString name, QString type, QUrl url)
{
    if (type == "LightSwitch") {
     RealLightSwitch realLight(name, url); 
     LightSwitchProxy lightSwitchProxy(&realLight);
     _lightSwitchProxy.push_back(&lightSwitchProxy);
    }
    if(type == "Thermostat"){
     RealThermostat realThermostat(name,url);
     ThermostatProxy thermostatProxy(&realThermostat);
     _thermostatProxy.push_back(&thermostatProxy);
    }
    if(type == "SprinklerSystem"){
     RealSprinklerSysem realSprinklerSystem(name,url);
     SprinklerSystemProxy sprinklerSystemProxy(&realSprinklerSystem);
     _sprinklerSystemProxy.push_back(&sprinklerSystemProxy);
    }
}

void RealController::registeredDevices()
{
    for(int unsigned i = 0; i < _lightSwitchProxy.size(); i++){
        _lightSwitchProxy[i];
    }
    for(int unsigned i = 0; i < _thermostatProxy.size(); i++){
        _thermostatProxy[i];
    }
    for(int unsigned i = 0; i < _sprinklerSystemProxy.size(); i++){
        _sprinklerSystemProxy[i];
    }
}
