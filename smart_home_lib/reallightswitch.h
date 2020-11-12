#ifndef REALLIGHTSWITCH_H
#define REALLIGHTSWITCH_H
#include "lightswitch.h"
#include "controllerproxy.h"

class LightSwitchProxy;
class RealLightSwitch : public LightSwitch
{
public:
    RealLightSwitch(QString id, QUrl url);
    virtual ~RealLightSwitch();
    void turnOn() override;
    void turnOff() override;
    void dim() override;
    void brighten() override;
};

#endif // REALLIGHTSWITCH_H
