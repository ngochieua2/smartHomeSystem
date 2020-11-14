#ifndef REALTHERMOSTAT_H
#define REALTHERMOSTAT_H

#include <thermostat.h>
#include <controllerproxy.h>

class ControllerProxy;

class RealThermostat : public Thermostat
{
public:
    RealThermostat();
    RealThermostat(QString id, QUrl URL);
    virtual ~RealThermostat();

    void createControllerProxy();

    ControllerProxy* getControllerProxy();

    void getDeviceInfo() override;

    void updateMeasurement();

    QList <Measurement*> currentState();

    void getMeasurement() override;

private:
    ControllerProxy* _controllerProxy{};
    DeviceInfo* _deviceInfo{nullptr};

    double _lastPoint{};
    double _currentPoint{};
    int _state{};

    Measurement* _measurement{nullptr};
    QList <Measurement*> _mesurementList{};
};

#endif // REALTHERMOSTAT_H
