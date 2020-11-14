#include "realsprinklersystem.h"

RealSprinklerSystem::RealSprinklerSystem()
{
    
}

RealSprinklerSystem::RealSprinklerSystem(QString id, QUrl url)
{
    _device_id = id;
    _devideType = "sprinkler System";
    _deviceUrl = url;
}

RealSprinklerSystem::~RealSprinklerSystem()
{
    
}


void RealSprinklerSystem::turnOn()
{
    OnOffState = true;    
}

void RealSprinklerSystem::turnOff()
{
    OnOffState = false;    
}

void RealSprinklerSystem::schedule(int delay, int duration)
{
    QDateTime currentTime;
    if(OnOffState == true){
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

bool RealSprinklerSystem::getState()
{
    return OnOffState;
}

QTimer *RealSprinklerSystem::getTimer()
{
    return _timer;
}
