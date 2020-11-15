#ifndef FILTERS_H
#define FILTERS_H
#include "measurement.h"
#include <QVariant>

class filter: public Measurement
{
public:
    filter();
    /*!
     * @brief minimumValueConversion given a specified minimum value, the output value
     * will be generated if the value from child measurement is greater than (or equal
     * to, if inclusive is set) the specified minimum; otherwise the value is propagated
     * without change  
     */
    bool minimumValueConversion(QVariant);
    /*!
     * @brief maximumValueConversion given a specified maximum value, the output value 
     * will be generated if the value from the child measurement is less than (or equal 
     * to, if inclusive is set) the specified maximum; otherwise the value is propagated 
     * without change
     */
    bool maximumValueConversion(QVariant);
    /*!
     * @brief exactValueConversion given a specified value, the output value will be 
     * generated if the value from the child measurement matches the specified value; 
     * if it does not match and an optional 'else' value is provided, the 'else' value 
     * will be generated, otherwise the original value will be propagated without change.
     */
    bool exactValueConversion(QVariant);

};

#endif // FILTERS_H

