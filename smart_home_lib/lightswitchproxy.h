#ifndef LIGHTSWITCHPROXY_H
#define LIGHTSWITCHPROXY_H

#include <lightswitch.h>
#include <reallightswitch.h>

class RealLightSwitch;

class LightSwitchProxy : public LightSwitch
{
public:
    LightSwitchProxy();
    LightSwitchProxy(QString id, QUrl URL);
    virtual ~LightSwitchProxy();

    QString getID();

    void turnOn() override;

    void turnOff() override;

    void dim() override;

    void brighten() override;

    void passRealLightSwitch(RealLightSwitch* realLightSwitch);

    void getDeviceInfo() override;

private:
    RealLightSwitch* _realLightSwitch{nullptr};
};

#endif // LIGHTSWITCHPROXY_H
