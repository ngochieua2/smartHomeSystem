#ifndef REALTHERMOSTAT_H
#define REALTHERMOSTAT_H

//For random
#include <stdlib.h>
#include <time.h>

#include <thermostat.h>
#include <controllerproxy.h>

class ControllerProxy;

class RealThermostat : public Thermostat
{
public:
    RealThermostat();
    RealThermostat(QString id, QUrl URL);
    virtual ~RealThermostat();

    QList <Measurement*> LastMeasurement();

    void getLastMeasurement() override;

    QList <Measurement*> Last5Measurement();

    void getLast5Measurement() override;

    QList <Measurement*> setPointMeasurement();

    void SetPoint(double setPoint) override;

    void warmer(double amount) override;

    void cooler(double amount) override;


    void createControllerProxy();

    ControllerProxy* getControllerProxy();

    void getDeviceInfo() override;

    QList <Measurement*> currentState();

    void getMeasurement() override;

    void UpdateState();

    void UpdateTemperature();

    bool isSameValue();

    void Update() override;


private:
    ControllerProxy* _controllerProxy{};
    DeviceInfo* _deviceInfo{nullptr};

    double _setPoint{};
    double _temperature{};
    int _state{};

    Measurement* _measurement{nullptr};
    QList <Measurement*> _mesurementList{};

    QList <Measurement*> _measurementRecord{};
};

#endif // REALTHERMOSTAT_H
