#ifndef LIGHTSWITCHPROXY_H
#define LIGHTSWITCHPROXY_H
#include "smarthomedevices.h"
#include "reallightswitch.h"

class RealLightSwitch;
class RealController;
class LightSwitchProxy : public LightSwitch
{
public:
    //LightSwitchProxy(RealLightSwitch* realLight);
    LightSwitchProxy(QString id, QUrl url);
    ~LightSwitchProxy();
    void turnOn() override;
    void turnOff() override;
    void dim() override;
    void brighten() override;
    void setRealLight(RealLightSwitch* realLight);
    //void setControllerProxy(ControllerProxy *controllerProxy) override;
private:
    RealLightSwitch* _realLight{};
};

#endif // LIGHTSWITCHPROXY_H
