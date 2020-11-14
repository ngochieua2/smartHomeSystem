#include "realcontroller.h"

RealController::RealController()
{
}

RealController::RealController(QString id, QUrl Url)
{
    _controller_id = id;
    _controller_Url = Url;
}

RealController::~RealController()
{
    for(int i = 0; i <_lightSwitchProxyList.size(); ++i){
        delete _lightSwitchProxyList.at(i);
    }
    for(int i = 0; i <_thermostatProxyList.size(); ++i){
        delete _thermostatProxyList.at(i);
    }
    for(int i = 0; i < _sprinklerSystemProxyList.size(); i++){
        delete _sprinklerSystemProxyList.at(i);
    }
    for(int i = 0; i < _deviceInfoList.size(); i++){
        delete _deviceInfoList.at(i);
    }
    for(int i = 0; i < _measurementList.size(); i++){
        delete _measurementList.at(i);
    }
}

QString RealController::getID()
{
    return _controller_id;
}

void RealController::registerDevice(QString name, QString type, QUrl URL)
{
    if(type == "lightSwitch"){
        _lightSwitchProxyList.append(new LightSwitchProxy(name, URL));
    }
    else if (type == "thermostat") {
        _thermostatProxyList.append(new ThermostatProxy(name,URL));
    }
    else if (type == "sprinklerSystem") {
        _sprinklerSystemProxyList.append(new SprinklerSystemProxy(name,URL));
    }
}

QString RealController::registerDevice()
{
    QString data{};
    if(_deviceInfoList.isEmpty()){
        data = "There is no register devices\n"
                "Please come back to main Menu and register new device\n\n";
    }
    else {
        for(int i = 0; i <_deviceInfoList.size(); i++ ){
            data +=  QString::number(i+1) + ". " + _deviceInfoList.at(i)->showDeviceInfo();
        }
    }
    _deviceInfoList.clear();
    return data;
}

void RealController::unregisterDevice(QString name)
{
    for (int i = 0; i < _lightSwitchProxyList.size(); i++ ){
        if(name == _lightSwitchProxyList.at(i)->getID()){
            _lightSwitchProxyList.removeAt(i);
            break;
        }
    }
    for (int i = 0; i < _thermostatProxyList.size(); i++ ){
        if(name == _thermostatProxyList.at(i)->getID()){
            _thermostatProxyList.removeAt(i);
            break;
        }
    }
    for (int i = 0; i < _sprinklerSystemProxyList.size(); i++ ){
        if(name == _sprinklerSystemProxyList.at(i)->getID()){
            _sprinklerSystemProxyList.removeAt(i);
            break;
        }
    }
}

LightSwitchProxy *RealController::getLightSwitchProxy()
{
    return _lightSwitchProxyList.last();
}

QList<LightSwitchProxy *> RealController::getLightSwitchProxyList()
{
    return _lightSwitchProxyList;
}

ThermostatProxy *RealController::getThermostatProxy()
{
    return _thermostatProxyList.last();
}

QList<ThermostatProxy *> RealController::getThermostatProxyList()
{
    return _thermostatProxyList;
}

SprinklerSystemProxy *RealController::getSprinklerSystemProxy()
{
    return _sprinklerSystemProxyList.last();
}

QList<SprinklerSystemProxy *> RealController::getSprinklerSystemProxyList()
{
    return _sprinklerSystemProxyList;
}

void RealController::receiveDeviceInfo(DeviceInfo *deviceInfo)
{
    _deviceInfoList.append(deviceInfo);
}



void RealController::report(QList<Measurement *> measurementList)
{
    _measurementList = measurementList;
}

QString RealController::currentState(QString name, QString Type)
{
    QString data{};
    if(Type == "lightSwitch" || Type == "All"){
        //Get measrement

        if(_lightSwitchProxyList.isEmpty()){
            data += "\nThere is no Light Switch device\n";
        }
        else {
            data += "\nLight Switch Devices: \n";
            for(int i = 0; i < _lightSwitchProxyList.size(); i++){
                // get info
                _lightSwitchProxyList.at(i)->getMeasurement();
                //Save info for 1 device
                data += QString::number(i+1) + ". " + _measurementList.at(0)->deviceName();
                for (int j = 0; j < _measurementList.size(); j++){
                    data += "- " + _measurementList.at(j)->displayMeasurement();
                }
                data += _measurementList.at(0)->getTakenTime();
            }
        }

    }
    else {
        return "Error\n";
    }

    return data;
}






