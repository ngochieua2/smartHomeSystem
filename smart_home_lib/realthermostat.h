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

private:
    ControllerProxy* _controllerProxy{};
    DeviceInfo* _deviceInfo{nullptr};
};

#endif // REALTHERMOSTAT_H
