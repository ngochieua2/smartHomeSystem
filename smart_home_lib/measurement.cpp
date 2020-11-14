#include "measurement.h"

Measurement::Measurement()
{

}

Measurement::Measurement(QString deviceName, Measurement::measurementType type, QVariant value)
{
    _deviceName = deviceName;
    _type = type;
    _value = value;
    _timestamp = QDateTime::currentDateTime();
}

Measurement::~Measurement()
{
    delete _rawMeasurement;
}

QString Measurement::deviceName()
{
    return "Device name: " + _deviceName + "\n";
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

QString Measurement::displayMeasurement()
{
    QString string;
    if(_type == measurementType::lightSwitchOnOff){
        string += "Device status: " + _value.toString() + unitOfMeasure() + "\n";
    }
    else if (_type == measurementType::brightnessLevel) {
        string += "Brightness Level: " + _value.toString() + unitOfMeasure() + "\n";
    }

    return string;
}

QString Measurement::getTakenTime()
{
    return "Taken time: " + _timestamp.toString("H:m:s MMM dd yyyy") + "\n\n";
}
