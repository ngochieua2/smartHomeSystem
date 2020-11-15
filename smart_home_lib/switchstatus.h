#ifndef SWITCHSTATUS_H
#define SWITCHSTATUS_H

#include "filter.h"

class SwitchStatus:public filter
{
public:
    SwitchStatus();
    /*!
     * @brief switchConversion changes the state value of light switch
     * @return state
     */
    QString switchConversion();
};

#endif // SWITCHSTATUS_H
