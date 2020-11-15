
#ifndef SWITCHSTATUS_H
#define SWITCHSTATUS_H

#include "filter.h"

class SwitchStatus:public filter
{
public:
    //SwitchStatus();
    SwitchStatus(QString deviceName, Measurement::measurementType type, QVariant value);

    QString switchConversion();
};

#endif // SWITCHSTATUS_H
