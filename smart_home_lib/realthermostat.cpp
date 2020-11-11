#include "realthermostat.h"

RealThermostat::RealThermostat(QString id, QUrl url)
{
    
}

double RealThermostat::setpoint(double desiredTemp)
{
    currentTemp = desiredTemp;
    return  currentTemp;
}

void RealThermostat::warmer(double amount)
{
    if (amount > 0){
        currentTemp += amount;
    }
}

void RealThermostat::cooler(double amount)
{
    if (amount > 0){
        currentTemp -= amount;
    }
}
