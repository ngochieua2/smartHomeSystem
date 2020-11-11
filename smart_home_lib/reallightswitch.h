#ifndef REALLIGHTSWITCH_H
#define REALLIGHTSWITCH_H
#include "lightswitch.h"

class RealLightSwitch : public LightSwitch
{
public:
    RealLightSwitch();
    RealLightSwitch(QString id, QUrl url);
    ~RealLightSwitch();
};

#endif // REALLIGHTSWITCH_H
