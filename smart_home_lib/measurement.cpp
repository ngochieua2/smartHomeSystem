#include "measurement.h"

Measurement::Measurement()
{

}

Measurement::~Measurement()
{

}

QString Measurement::deviceName()
{
    return _deviceName;
}

QDateTime Measurement::timestamp()
{
    return _timestamp;
}

QVariant Measurement::value()
{
    return _value;
}

QString Measurement::unitOfMeasure()
{
    if (_type == measurementType::temperature || _type == measurementType::temperatureSetpoint){
        return "C";
    }
    else if (_type == measurementType::waterUsage || _type == measurementType::totalWaterUsage) {
        return "L";
    }
    else if (_type == measurementType::brightnessLevel) {
        return "%";
    }
    else if (_type == measurementType::scheduledDuration) {
        return "S";
    }
    else{
        return "";
    }
}

bool Measurement::isFiltered()
{
    return false;
}

Measurement *Measurement::rawMeasurement()
{
    return _rawMeasurement;
}
