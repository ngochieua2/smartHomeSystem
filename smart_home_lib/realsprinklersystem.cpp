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


void RealSprinklerSystem::turnOn()
{
    OnOffState = true;    
}

void RealSprinklerSystem::turnOff()
{
    OnOffState = false;    
}

void RealSprinklerSystem::schedule(QDateTime delay, int duration)
{
    QDateTime currentTime;
    QTimer timer;
    if(currentTime.currentDateTime() == delay){       
        timer.setInterval(duration);
        if(OnOffState == true){
            OnOffState = false;
        } else {
            OnOffState = true;
        }   
    }
    
}

void RealSprinklerSystem::createControllerProxy()
{
    _controllerProxy = new ControllerProxy();    
}

ControllerProxy *RealSprinklerSystem::getControllerProxy()
{
    return _controllerProxy;    
}
