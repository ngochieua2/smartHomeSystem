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
}

RealSprinklerSystem::~RealSprinklerSystem()
{
    delete _deviceInfo;
    delete _controllerProxy;
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

void RealSprinklerSystem::getDeviceInfo()
{
    _controllerProxy->receiveDeviceInfo(_deviceInfo);
    _deviceInfo = new DeviceInfo(_device_id,_devideType,_deviceUrl);
    _deviceInfo->updateTime();
}
