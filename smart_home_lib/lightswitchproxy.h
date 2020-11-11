#ifndef LIGHTSWITCHPROXY_H
#define LIGHTSWITCHPROXY_H
#include "lightswitch.h"

class LightSwitchProxy : public LightSwitch
{
public:
    LightSwitchProxy();
    ~LightSwitchProxy();
    LightSwitchProxy(QString id, QString type, QUrl url);
};

#endif // LIGHTSWITCHPROXY_H
