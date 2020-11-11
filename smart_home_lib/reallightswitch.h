#ifndef REALLIGHTSWITCH_H
#define REALLIGHTSWITCH_H
#include "lightswitch.h"

class RealLightSwitch : public LightSwitch
{
public:
    RealLightSwitch();
    RealLightSwitch(QString deviceId,QString deviceType, QUrl url);
    ~RealLightSwitch();
};

#endif // REALLIGHTSWITCH_H
