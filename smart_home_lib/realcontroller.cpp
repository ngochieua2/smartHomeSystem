#include "realcontroller.h"

void RealController::registerDevice(QString id, QString type, QUrl url)
{
    if (type == "LightSwitch") { 
    LightSwitchProxy lightSwitchProxy(id,url);        
    _lightSwitchProxy.push_back(&lightSwitchProxy);
    }
    if(type == "Thermostat"){
    ThermostatProxy thermostatProxy(id,url);
    _thermostatProxy.push_back(&thermostatProxy);
    }
    if(type == "SprinklerSystem"){
     SprinklerSystemProxy sprinklerSystemProxy(id,url);
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

void RealController::unregisterDevice(QString id)
{
    for (int unsigned i = 0; i < _lightSwitchProxy.size(); i++){
        if(id == _lightSwitchProxy[i]->getId()){
            _lightSwitchProxy.erase(std::remove(_lightSwitchProxy.begin(), _lightSwitchProxy.end(), _lightSwitchProxy[i]), _lightSwitchProxy.end());
        }
    }
    for (int unsigned i = 0; i < _thermostatProxy.size(); i++){
        if(id == _thermostatProxy[i]->getId()){
            _thermostatProxy.erase(std::remove(_thermostatProxy.begin(), _thermostatProxy.end(), _thermostatProxy[i]), _thermostatProxy.end());
        }
    }
    for (int unsigned i = 0; i < _lightSwitchProxy.size(); i++){
        if(id == _sprinklerSystemProxy[i]->getId()){
            _sprinklerSystemProxy.erase(std::remove(_sprinklerSystemProxy.begin(), _sprinklerSystemProxy.end(), _sprinklerSystemProxy[i]), _sprinklerSystemProxy.end());
        }
    }
}


QString RealController::configController(QString id, QUrl URL)
{
    
    return "Success";
}
