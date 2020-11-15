#include "filter.h"

filter::filter(QString deviceName, Measurement::measurementType type, QVariant value):
   Measurement(deviceName,type,value)
{

}
QVariant filter::minimumValueConversion(QVariant val){
    if(val.type() == QVariant::Double || val.type() == QVariant::Int)
    {
        double dval = devicevalue.value<double>();
        double dval2 = val.value<double>();
        if(dval > dval2)
        {
            devicevalue = val;
            return true;
        }

    }else if(val.type() == QVariant::Bool)
    {
        bool sta = val.value<bool>();
        if(!sta)
        {
             devicevalue = val;
             return true;
        }
    }
    return false;
}
QVariant filter::maximumValueConversion(QVariant val){
    if(val.type() == QVariant::Double || val.type() == QVariant::Int){
        double dval = devicevalue.value<double>();
        double dval2 = val.value<double>();
        if(dval < dval2){
            devicevalue = val;
            return devicevalue;
        }

    }else if(val.type() == QVariant::Bool)
    {
        bool sta = val.value<bool>();
        if(sta)
        {
             devicevalue = val;
             return devicevalue;
        }

    }
    return false;
}

QVariant filter::exactValueConversion(QVariant val){
    if(val == devicevalue){
        devicevalue = val;
        return devicevalue;
    }
    return true;
}

TemperatureFilter::TemperatureFilter(QString deviceName, Measurement::measurementType type, QVariant value)
    :filter(deviceName,type,value)
{

}

QVariant TemperatureFilter::temperatureConversion()
{
     QString unit = this->unitOfMeasure();

     if(unit == "F")
     {

         if(maximumValueConversion(this->value()) <= 0)
         {
             devicevalue = "freezing";
         }
         else if(maximumValueConversion(this->value()) <= 15 && maximumValueConversion(this->value()) > 0)
         {
             devicevalue = "cold";
         }
         else if(maximumValueConversion(this->value()) < 28 && maximumValueConversion(this->value()) > 15)
         {
             devicevalue = "balmy";
         }
         else if(maximumValueConversion(this->value()) >= 28 && maximumValueConversion(this->value()) > 40)
         {
             devicevalue = "hot";
         }
         else if(maximumValueConversion(this->value()) >= 40)
         {
             devicevalue = "scorching";
         }
         else
         {
             return false;
         }
     }
     else if(unit == "C")
     {


         QVariant currentValue((this->value().toDouble() - 32.0) / 1.8);

         if(currentValue <= 0)
         {
             devicevalue = "freezing";
         }
         else if(currentValue <= 15 && currentValue > 0)
         {
             devicevalue = "cold";
         }
         else if(currentValue < 28 && currentValue > 15)
         {
             devicevalue = "balmy";
         }
         else if(currentValue >= 28 && currentValue > 40)
         {
             devicevalue = "hot";
         }
         else if(currentValue >= 40)
         {
             devicevalue = "scorching";
         }
         else
         {
             return false;
         }


     }

     return devicevalue;
}

SwitchStatusFilter::SwitchStatusFilter(QString deviceName, Measurement::measurementType type, QVariant value)
    :filter(deviceName,type,value)
{

}

QVariant SwitchStatusFilter::switchFilterConversion()
{

    if(static_cast<int>(measurementType::lightSwitchOnOff) == 1)
    {
        if(exactValueConversion(this->value()).toBool() == true)
        {
            devicevalue = "NO";
            return devicevalue;
        }
        else if(exactValueConversion(this->value()).toBool() == false)
        {
            devicevalue = "OFF";
            return devicevalue;
        }
    }

    return false;
}
