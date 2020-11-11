#include "thermostat.h"

Thermostat::Thermostat()
{
    currentTemp = lastTemp;
}

Thermostat::~Thermostat()
{
}

double Thermostat::setpoint(double desiredTemp)
{
    currentTemp = desiredTemp;
    return  currentTemp;
}

void Thermostat::warmer(double amount)
{
    if (amount > 0){
        currentTemp += amount;
    }
}

void Thermostat::cooler(double amount)
{
    if (amount > 0){
        currentTemp -= amount;
    }
}
