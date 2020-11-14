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
    
    void turnOn() override;
    
    void turnOff() override;
    
    
    void getMeasurement() override;
    
    void updateMeasurement();   
    
    QList <Measurement*> currentState();
    
    QList <Measurement*> waterUsage();
    
    void createControllerProxy();

    ControllerProxy* getControllerProxy();
    
    
    QString getState();
    
    QTimer* getTimer();
    
private:
    QString _state{};
    QDateTime _time{};
    int _duration{};
    double _waterConsumption{};
    
    QTimer* _timer{};
    ControllerProxy* _controllerProxy{};
    Measurement* _measurement{nullptr};
    QList <Measurement*> _measurementList{};
};

#endif // REALSPRINKLERSYSTEM_H
