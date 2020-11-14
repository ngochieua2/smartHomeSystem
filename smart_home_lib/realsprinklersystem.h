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

    void schedule(int delay, int duration) override;

    void createControllerProxy();

    ControllerProxy* getControllerProxy();

    void getDeviceInfo() override;

    void getMeasurement() override;

    QList <Measurement*> currentState();

    double calWaterUsage();
    
    QList<Measurement*> waterUsage();
    
    void recordCurrentCheckingTime();

    QString getState();

    QTimer* getTimer();

    void updateMeasurement();

private:
    QString _state{};
    QDateTime _time{};
    
    QDateTime _start{};
    QDateTime _end{};
    int _record{};
    QList<double> _records{};
    
    int _duration{};
    int _updateFrequency{};
    
    double _waterConsumptionpPerInt{};
    double _totalWaterConsumption{};   
    
    QTimer* _timer{};
    ControllerProxy* _controllerProxy{};

    DeviceInfo* _deviceInfo{nullptr};

    Measurement* _measurement{nullptr};
    QList <Measurement*> _measurementList{};

};

#endif // REALSPRINKLERSYSTEM_H
