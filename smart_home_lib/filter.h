#ifndef FILTERS_H
#define FILTERS_H
#include "measurement.h"
#include <QVariant>

class filter: public Measurement
{
public:
    filter(QString deviceName, Measurement::measurementType type, QVariant value);
    QVariant minimumValueConversion(QVariant);
    QVariant maximumValueConversion(QVariant);
    QVariant exactValueConversion(QVariant);

};

class TemperatureFilter : public filter
{
    TemperatureFilter(QString deviceName, Measurement::measurementType type, QVariant value);
    QVariant temperatureConversion();
};

class SwitchStatusFilter : public filter
{
    SwitchStatusFilter(QString deviceName, Measurement::measurementType type, QVariant value);
    QVariant switchFilterConversion();
};

#endif // FILTERS_H

