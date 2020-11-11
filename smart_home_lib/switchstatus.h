
#ifndef SWITCHSTATUS_H
#define SWITCHSTATUS_H

#include "filters.h"

class SwitchStatus:public Filters
{
public:
    SwitchStatus();
    QString switchConversion();
};

#endif // SWITCHSTATUS_H
