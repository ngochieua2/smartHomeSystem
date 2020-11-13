#ifndef REALTHERMOSTAT_H
#define REALTHERMOSTAT_H
#include "thermostat.h"

class RealThermostat : public Thermostat
{
public:
    RealThermostat(QString id, QUrl url);
    ~RealThermostat();
};

#endif // REALTHERMOSTAT_H
