#include "realsprinklersystem.h"

RealSprinklerSystem::RealSprinklerSystem()
{

}

RealSprinklerSystem::RealSprinklerSystem(QString id, QUrl url)
{
    _device_id = id;
    _devideType = "Sprinkler System";
    _deviceUrl = url;
    _deviceInfo = new DeviceInfo(_device_id,_devideType,_deviceUrl);

    //default value
    _state = "OFF";
    _waterConsumptionpPerInt = 0.3;
    _duration = 0;
    _delay = 0;
    _updateFrequency = 5000;
    _time.setTime(QTime());
    _currentWaterConsumption = 0;
    _totalWaterConsumption = 0;
    
    //Record default measurements
    _measurement = new Measurement(_device_id, Measurement::measurementType::sprinklerState, _state);
    _measurementRecord.append(_measurement);
    _measurement = new Measurement(_device_id, Measurement::measurementType::scheduledTime, _time);
    _measurementRecord.append(_measurement);
    _measurement = new Measurement(_device_id, Measurement::measurementType::scheduledDuration, _duration);
    _measurementRecord.append(_measurement);
}

RealSprinklerSystem::~RealSprinklerSystem()
{
    delete _deviceInfo;
    delete _controllerProxy;
    delete  _timer;
    delete  _measurement;
    for(int i = 0; i < _measurementList.size(); i++){
        delete _measurementList.at(i);
    }
    for(int i = 0; i < _measurementRecord.size(); i++){
        delete _measurementRecord.at(i);
    }
}

void RealSprinklerSystem::turnOn()
{
    _state = "ON";
    _start.setTime(QTime());
    _end.setTime(QTime());
    _delay = 0;
    _duration = 0;
}
void RealSprinklerSystem::turnOff()
{
    _state = "OFF";      
    _start.setTime(QTime());
    _end.setTime(QTime());
    _delay = 0;
    _duration = 0;
    

}
void RealSprinklerSystem::getMeasurement()
{
    _controllerProxy->report(currentState());
}

void RealSprinklerSystem::getCurrentWaterConsumption()
{
    _controllerProxy->report(latestWaterConsumption());
}

void RealSprinklerSystem::getTotalWaterConsumption()
{
    _controllerProxy->report(totalWaterConsumption());
}

void RealSprinklerSystem::UpdateWaterUsage()
{
}

bool RealSprinklerSystem::isValueChanged()
{
    for (int i = _measurementRecord.size() - 2; i >= 0; i--){
            if(_measurementRecord.last()->getType() == _measurementRecord.at(i)->getType()){
                if(_measurementRecord.last()->value() == _measurementRecord.at(i)->value()){
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    return false;    
}

QList<Measurement *> RealSprinklerSystem::latestWaterConsumption()
{
    _measurementList.clear();
    for (int i = _measurementRecord.size()-1; i >= 0; i--){
            if(_measurementRecord.at(i)->getType() == Measurement::measurementType::waterUsage){
                _measurement = new Measurement(_device_id,Measurement::measurementType::waterUsage,_measurementRecord.at(i)->value());
                _measurementList.append(_measurement);
                break;
            }
    }
    return _measurementList;    
}

QList<Measurement *> RealSprinklerSystem::totalWaterConsumption()
{
    _measurementList.clear();
    for (int i = _measurementRecord.size()-1; i >= 0; i--){
            if(_measurementRecord.at(i)->getType() == Measurement::measurementType::totalWaterUsage){
                _measurement = new Measurement(_device_id,Measurement::measurementType::totalWaterUsage,_measurementRecord.at(i)->value());
                _measurementList.append(_measurement);
                break;
            }
    }
    return _measurementList;    
}


QList<Measurement *> RealSprinklerSystem::currentState(){
    _measurementList.clear();
    _measurement = new Measurement(_device_id, Measurement::measurementType::sprinklerState, _state);
    _measurementList.append(_measurement);
    _measurement = new Measurement(_device_id, Measurement::measurementType::scheduledTime, _time);
    _measurementList.append(_measurement);
    _measurement = new Measurement(_device_id, Measurement::measurementType::scheduledDuration, _duration);
    _measurementList.append(_measurement);
    return _measurementList;
}
QList<Measurement*> RealSprinklerSystem::waterUsage(){
    _measurementList.clear();
    _measurement = new Measurement(_device_id, Measurement::measurementType::waterUsage, _currentWaterConsumption);
    _measurementList.append(_measurement);
    _measurement = new Measurement(_device_id, Measurement::measurementType::totalWaterUsage, _totalWaterConsumption);
    _measurementList.append(_measurement);
    return _measurementList;
}

void RealSprinklerSystem::schedule(int delay, int duration)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    if(_state == "ON"){
        turnOff();
        _state = "SCHEDULED";
    }
    _delay = delay;
    _duration = duration;
    _start = currentTime.addSecs(delay);
    _end = currentTime.addSecs(delay + duration);
    
}

void RealSprinklerSystem::createControllerProxy()
{
    _controllerProxy = new ControllerProxy();
}

ControllerProxy *RealSprinklerSystem::getControllerProxy()
{
    return _controllerProxy;
}

void RealSprinklerSystem::getDeviceInfo()
{
    _controllerProxy->receiveDeviceInfo(_deviceInfo);
    _deviceInfo = new DeviceInfo(_device_id,_devideType,_deviceUrl);
    _deviceInfo->updateTime();
}


QTimer *RealSprinklerSystem::getTimer()
{
    return _timer;
}

