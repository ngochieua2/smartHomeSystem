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

    QList <Measurement*> waterUsage();

    QString getState();

    QTimer* getTimer();

    void updateMeasurement();

private:
    QString _state{};
    QDateTime _time{};
    int _duration{};
    double _waterConsumption{};

    QTimer* _timer{};
    ControllerProxy* _controllerProxy{};

    DeviceInfo* _deviceInfo{nullptr};

    Measurement* _measurement{nullptr};
    QList <Measurement*> _measurementList{};
};

#endif // REALSPRINKLERSYSTEM_H
