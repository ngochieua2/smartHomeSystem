#include "measurement.h"

Measurement::Measurement()
{

}

Measurement::Measurement(QString deviceName, Measurement::measurementType type, QVariant value)
{
    _deviceName = deviceName;
    _type = type;
    _value = value;
    //给变量赋值，这样就不会出现空值了
    devicevalue = value;
    _timestamp = QDateTime::currentDateTime();

//    if(_type == static_cast<int>(measurementType::temperature) || _type == static_cast<int>(measurementType::temperatureSetpoint))
//    {


//        double tempValue = std::round(_value.toDouble() * 100.00) / 100;
//        _value.clear();
//        _value.setValue(tempValue);

//    }
//    else if(_type == static_cast<int>(measurementType::scheduledDuration))
//    {
//        double tempValue = std::round(_value.toDouble() * 1000.00) / 1000;
//        _value.clear();
//        _value.setValue(tempValue);
//    }
//    else if(_type == static_cast<int>(measurementType::waterUsage))
//    {

//        double tempValue = std::round(_value.toDouble() * 10.00) / 10;
//        _value.clear();
//        _value.setValue(tempValue);
//    }
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
        string = "Device status: " + _value.toString() + unitOfMeasure() + "\n";
    }
    else if (_type == measurementType::brightnessLevel) {
        string = "Brightness Level: " + _value.toString() + unitOfMeasure() + "\n";
    }
    else if (_type == measurementType::temperature) {

        string = "Temperature: " + _value.toString() + unitOfMeasure() + "\n";
    }
    else if (_type == measurementType::temperatureSetpoint) {
        string = "Temperature setpoint: " + _value.toString() + unitOfMeasure() + "\n";
    }
    else if (_type == measurementType::thermostatState ) {
        string = "Thermostat state: " + _value.toString() + unitOfMeasure() + "\n";
    }
    else if (_type == measurementType::waterUsage ) {
        string = "Water usage: " + _value.toString() + unitOfMeasure() + "\n";
    }
    else if (_type == measurementType::scheduledTime ) {
        string = "Schedule time: " + _value.toDateTime().toString("H:m:s MMM dd yyyy") + unitOfMeasure() + "\n";
    }
    else if (_type == measurementType::totalWaterUsage) {
        string = "Total water usage: " + _value.toString() + unitOfMeasure() + "\n";
    }
    else if (_type == measurementType::scheduledDuration) {
        string = "Schedule duration: " + _value.toString() + unitOfMeasure() + "\n";
    }

    else if (_type == measurementType::sprinklerState) {
        string = "Sprinkler state: " + _value.toString() + unitOfMeasure() + "\n";
    }
    else {
        //do nothing
    }

    return string;
}

QString Measurement::getTakenTime()
{
    return "Taken time: " + _timestamp.toString("H:m:s MMM dd yyyy") + "\n\n";
}

Measurement::measurementType Measurement::getType()
{
    return _type;
}
