#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "filter.h"

class Temperature:public filter
{
public:
    //Temperature();
    Temperature(QString deviceName, Measurement::measurementType type, QVariant value);

    QString temperatureConversion(double val,QString type);
};

#endif // TEMPERATURE_H
