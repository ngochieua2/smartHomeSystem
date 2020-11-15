#ifndef REALLIGHTSWITCH_H
#define REALLIGHTSWITCH_H

#include <lightswitch.h>
#include <controllerproxy.h>

class ControllerProxy;

class RealLightSwitch : public LightSwitch
{
public:
    RealLightSwitch();
    RealLightSwitch(QString id, QUrl URL);
    virtual ~RealLightSwitch();

    void turnOn() override;

    void turnOff() override;

    void dim() override;

    void brighten() override;

    void createControllerProxy();

    ControllerProxy* getControllerProxy();

    void getDeviceInfo() override;

    QList <Measurement*> currentState();

    void getMeasurement() override;

    bool isSameValue();

private:
    bool OnOffState{};
    int brightnessLevel{};

    ControllerProxy* _controllerProxy{};

    DeviceInfo* _deviceInfo{nullptr};

    Measurement* _measurement{nullptr};
    QList <Measurement*> _mesurementList{};

    QList <Measurement*> _measurementRecord{};

};

#endif // REALLIGHTSWITCH_H
