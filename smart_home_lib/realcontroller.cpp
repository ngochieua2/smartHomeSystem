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
    int a = 0;
    if (name == ""){
        if(Type == "lightSwitch" || Type == "All"){
            //Get measurement

            if(_lightSwitchProxyList.isEmpty() && Type != "All"){
                data += "\nThere is no Light Switch device\n";
            }
            else if (_lightSwitchProxyList.isEmpty() && Type == "All") {
                // do nothing
            }
            else {
                data += "\nLight Switch Devices: \n";
                for(int i = 0; i < _lightSwitchProxyList.size(); i++){
                    // get info
                    _lightSwitchProxyList.at(i)->getMeasurement();
                    //Save info for 1 device
                    data += QString::number(++a) + ". " + _measurementList.at(0)->deviceName();
                    for (int j = 0; j < _measurementList.size(); j++){
                        data += "- " + _measurementList.at(j)->displayMeasurement();
                    }
                    data += _measurementList.at(0)->getTakenTime();
                }
            }
        }
        if(Type == "thermostat" || Type == "All"){
            //Get measurement
            if(_thermostatProxyList.isEmpty() && Type != "All"){
                data += "\nThere is no thermostat device\n";
            }
            else if(_thermostatProxyList.isEmpty() && Type == "All"){
                // do nothing
            }
            else {
                data += "\nTherostat Devices: \n";
                for(int i = 0; i < _thermostatProxyList.size(); i++){
                    // get info
                    _thermostatProxyList.at(i)->getMeasurement();
                    //Save info for 1 device
                    data += QString::number(++a) + ". " + _measurementList.at(0)->deviceName();
                    for (int j = 0; j < _measurementList.size(); j++){
                        data += "- " + _measurementList.at(j)->displayMeasurement();
                    }
                    data += _measurementList.at(0)->getTakenTime();
                }
            }
        }
        if(Type == "sprinklerSystem" || Type == "All"){
            //Get measurement

            if(_sprinklerSystemProxyList.isEmpty() && Type != "All"){
                data += "\nThere is no sprinkler system device\n\n";
            }
            else if(_sprinklerSystemProxyList.isEmpty() && Type == "All"){
                // do nothing
            }
            else {
                data += "\nTherostat Devices: \n";
                for(int i = 0; i < _sprinklerSystemProxyList.size(); i++){
                    // get info
                    _sprinklerSystemProxyList.at(i)->getMeasurement();
                    //Save info for 1 device
                    data += QString::number(++a) + ". " + _measurementList.at(0)->deviceName();
                    for (int j = 0; j < _measurementList.size(); j++){
                        data += "- " + _measurementList.at(j)->displayMeasurement();
                    }
                    data += _measurementList.at(0)->getTakenTime();
                }
            }
        }
        if (Type == "All" && data == ""){
            data = "\nThere is no device\n";
        }

    }
    else {
        bool run = false;
        for (int i = 0; i < _lightSwitchProxyList.size(); i++ ){
            if(name == _lightSwitchProxyList.at(i)->getID()){
                // get info
                _lightSwitchProxyList.at(i)->getMeasurement();
                //Save info for 1 device
                data +=  _measurementList.at(0)->deviceName();
                for (int j = 0; j < _measurementList.size(); j++){
                    data += "- " + _measurementList.at(j)->displayMeasurement();
                }
                data += _measurementList.at(0)->getTakenTime();
                run = true;
                break;
            }
        }
        for (int i = 0; i < _thermostatProxyList.size(); i++ ){
            if(name == _thermostatProxyList.at(i)->getID()){
                // get info
                _thermostatProxyList.at(i)->getMeasurement();
                //Save info for 1 device
                data += _measurementList.at(0)->deviceName();
                for (int j = 0; j < _measurementList.size(); j++){
                    data += "- " + _measurementList.at(j)->displayMeasurement();
                }
                data += _measurementList.at(0)->getTakenTime();
                run = true;
                break;
            }
        }
        for (int i = 0; i < _sprinklerSystemProxyList.size(); i++ ){
            if(name == _sprinklerSystemProxyList.at(i)->getID()){
                // get info
                _sprinklerSystemProxyList.at(i)->getMeasurement();
                //Save info for 1 device
                data += _measurementList.at(0)->deviceName();
                for (int j = 0; j < _measurementList.size(); j++){
                    data += "- " + _measurementList.at(j)->displayMeasurement();
                }
                data += _measurementList.at(0)->getTakenTime();
                run = true;
                break;
            }
        }
        if(!run){
            data = "\nThere are no device\n";
        }
    }
    _measurementList.clear();
    return data;
}

QString RealController::getUpdateMeasurement()
{
    QString data{};
    if(_measurementList.isEmpty()){
        data = "Nothing change in device\n";
    }
    else {
        data += _measurementList.at(0)->deviceName();
        for (int j = 0; j < _measurementList.size(); j++){
            data += "- " + _measurementList.at(j)->displayMeasurement();
        }
        data += _measurementList.at(0)->getTakenTime();
    }
    _measurementList.clear();
    return data;
}






