#ifndef FILTERS_H
#define FILTERS_H
#include "measurement.h"
#include <QVariant>

class Filters: public Measurement
{
public:
    Filters();
    bool minimumValueConversion(QVariant);
    bool maximumValueConversion(QVariant);
    bool exactValueConversion(QVariant);

};

#endif // FILTERS_H
