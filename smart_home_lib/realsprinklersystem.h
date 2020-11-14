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
    

    void schedule(int delay, int duration) override;
    void createControllerProxy();

    ControllerProxy* getControllerProxy();
    
    bool getState();
    
    QTimer* getTimer();
private:
    bool OnOffState{};
    int _updateFrequency{5000};
    double _waterConsumption{};
    QTimer* _timer{};
    ControllerProxy* _controllerProxy{};
public slots:
    void turnOn() override;
    void turnOff() override;
};

#endif // REALSPRINKLERSYSTEM_H
