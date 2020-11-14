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
    _state = "ON";
    _waterConsumptionpPerInt = 0.3;
    _duration = 0;
    _updateFrequency = 5000;
    _time.setTime(QTime());
    _currentWaterConsumption = 0;
    _totalWaterConsumption = 0;
    updateMeasurement();
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
    for(int i = 0; i < _trackWaterList.size(); i++){
        delete _trackWaterList.at(i);
    }
}

void RealSprinklerSystem::turnOn()
{
    schedule(0,0);
    _state = "ON";
    _start = QDateTime::currentDateTime();
}
void RealSprinklerSystem::turnOff()
{
    schedule(0,0);
    if (_state == "ON"){
        _state = "OFF";
        _end = QDateTime::currentDateTime();
        _record = _start.msecsTo(_end);
        _currentWaterConsumption = (_record/1000)* _waterConsumptionpPerInt;        
        _records.append(_record);
    }   
}
void RealSprinklerSystem::getMeasurement()
{
    updateMeasurement();
    _controllerProxy->report(currentState());
}

void RealSprinklerSystem::updateMeasurement()
{
    _measurementList.clear();
    _measurement = new Measurement(_device_id, Measurement::measurementType::sprinklerState, _state);
    _measurementList.append(_measurement);
    _measurement = new Measurement(_device_id, Measurement::measurementType::scheduledTime, _time);
    _measurementList.append(_measurement);
    _measurement = new Measurement(_device_id, Measurement::measurementType::scheduledDuration, _duration);
    _measurementList.append(_measurement);
}

QList<Measurement *> RealSprinklerSystem::currentState(){
    return _measurementList;
}
QList<Measurement*> RealSprinklerSystem::waterUsage(){
    _measurement = new Measurement(_device_id, Measurement::measurementType::waterUsage, _currentWaterConsumption);
    _trackWaterList.append(_measurement);
    _measurement = new Measurement(_device_id, Measurement::measurementType::totalWaterUsage, _totalWaterConsumption);
    _trackWaterList.append(_measurement);
    return _trackWaterList;
}

void RealSprinklerSystem::recordCurrentCheckingTime(){
    _end = QDateTime::currentDateTime();
    _record = _start.msecsTo(_end);
    _currentWaterConsumption = (_record/1000)* _waterConsumptionpPerInt;    
    _records.append(_record);
    _start = QDateTime::currentDateTime();
}
double RealSprinklerSystem::calWaterUsage()
{   
    double sum = 0;
    if(_records.count() > 0){
        for (double record : _records){
           sum = sum + record;
        }
        _totalWaterConsumption = (sum/1000)*_waterConsumptionpPerInt;
    }
    return _totalWaterConsumption;
}

void RealSprinklerSystem::schedule(int delay, int duration)
{
    QDateTime currentTime;
    if(_state == "ON"){
        turnOff();
        _state = "SCHEDULED";
    }
    QTimer::singleShot(delay,_timer,SLOT(turnOn()));
    QTimer::singleShot(duration,_timer,SLOT(turnOff()));
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

QString RealSprinklerSystem::getState()
{
    return _state;
}

QTimer *RealSprinklerSystem::getTimer()
{
    return _timer;
}

