#ifndef REALSPRINKLERSYSTEM_H
#define REALSPRINKLERSYSTEM_H
#include "controllerproxy.h"
#include "sprinklersystem.h"

class ControllerProxy;

class RealSprinklerSystem : public SprinklerSystem
{
public:
    RealSprinklerSystem();
    RealSprinklerSystem(QString id, QUrl url);
    virtual ~RealSprinklerSystem();

    void turnOn() override;

    void turnOff() override;

    void schedule(QDateTime delay, int duration) override;

    void createControllerProxy();

    ControllerProxy* getControllerProxy();

    void getDeviceInfo() override;

private:
    bool OnOffState{};
    int _updateFrequency{5000};
    double _waterConsumption{};

    ControllerProxy* _controllerProxy{};

    DeviceInfo* _deviceInfo{nullptr};
};

#endif // REALSPRINKLERSYSTEM_H
