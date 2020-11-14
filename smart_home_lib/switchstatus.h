
#ifndef SWITCHSTATUS_H
#define SWITCHSTATUS_H

#include "filter.h"

class SwitchStatus:public filter
{
public:
    SwitchStatus();
    QString switchConversion();
};

#endif // SWITCHSTATUS_H
