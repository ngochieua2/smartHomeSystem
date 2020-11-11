#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "filters.h"

class Temperature:public Filters
{
public:
    Temperature();
    QString temperatureConversion(double val,QString type);
};

#endif // TEMPERATURE_H
