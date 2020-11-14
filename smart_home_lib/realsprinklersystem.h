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
    
    void getWaterUsage() override;
    
    void UpdateWaterUsage();

    QList <Measurement*> currentState();
    
    QList<Measurement*> waterUsage();
    
    QString getState();

    QTimer* getTimer();
    
    bool isValueChanged();
    
    QList<Measurement*> latestWaterConsumption();
    
    QList<Measurement*> totalWaterConsumption();
    
    void updateTime() override;
    
    void turnOnByScheduling();
    
private:
    QString _state{};
    QDateTime _time{};
    
    QDateTime _start{};
    QDateTime _end{};
    
    int _duration{};
    int _delay{};
    int _updateFrequency{};
    
    double _waterConsumptionpPerInt{};
    double _currentWaterConsumption{};
    double _totalWaterConsumption{};   
    
    QTimer* _timer{};
    ControllerProxy* _controllerProxy{};

    DeviceInfo* _deviceInfo{nullptr};

    Measurement* _measurement{nullptr};
    QList <Measurement*> _measurementList{};
    QList <Measurement*> _measurementRecord{};

};

#endif // REALSPRINKLERSYSTEM_H
