#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "filter.h"

class Temperature:public filter
{
public:
    Temperature();
    /*!
     * @brief temperatureConversion convert a Fahrenheit temperature into a Celsius temperature, 
     * then convert the Celsius temperature into an appropriate descriptive string 
     * @param val
     * @param type
     * @return description
     */
    QString temperatureConversion(double val,QString type);
};

#endif // TEMPERATURE_H
