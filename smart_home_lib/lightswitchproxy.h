#ifndef LIGHTSWITCHPROXY_H
#define LIGHTSWITCHPROXY_H
#include "lightswitch.h"
#include "reallightswitch.h"
#include "lightswitchfactory.h"

class LightSwitchProxy : public LightSwitch
{
public:
    LightSwitchProxy(RealLightSwitch* realLight);
    ~LightSwitchProxy();
    LightSwitchProxy(QString id, QString type, QUrl url);
private:
    RealLightSwitch* _realLight{};
    LightSwitchFactory* _factory{};
};

#endif // LIGHTSWITCHPROXY_H
