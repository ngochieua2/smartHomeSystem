#include "realsprinklersystem.h"

RealSprinklerSystem::RealSprinklerSystem()
{
    
}

RealSprinklerSystem::RealSprinklerSystem(QString id, QUrl url)
{
    _device_id = id;
    _devideType = "sprinkler System";
    _deviceUrl = url;
    
    //default value
    
    _state = "ON";
    _waterConsumption = 0;
    _duration = 0;
    _time.setTime(QTime());
    updateMeasurement();
}

RealSprinklerSystem::~RealSprinklerSystem()
{
    
}


void RealSprinklerSystem::turnOn()
{
    _state = "ON";    
}

void RealSprinklerSystem::turnOff()
{
    _state = "OFF";    
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

QList<Measurement *> RealSprinklerSystem::currentState()
{
    return _measurementList;
}

QList<Measurement *> RealSprinklerSystem::waterUsage()
{
    
}

void RealSprinklerSystem::schedule(int delay, int duration)
{
    QDateTime currentTime;
    if(_state == true){
        turnOff();
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

QString RealSprinklerSystem::getState()
{
    return _state;
}

QTimer *RealSprinklerSystem::getTimer()
{
    return _timer;
}
