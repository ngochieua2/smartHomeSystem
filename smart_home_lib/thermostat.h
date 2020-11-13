#ifndef THERMOSTAT_H
#define THERMOSTAT_H
#include "smarthomedevice.h"

class Thermostat : public SmartHomeDevice
{
public:
    Thermostat(QString id, QUrl url);
    ~Thermostat();
};

#endif // THERMOSTAT_H
