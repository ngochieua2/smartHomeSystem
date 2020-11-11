#include "filters.h"

Filters::Filters()
{

}

bool Filters::minimumValueConversion(QVariant val){
    if(val.type() == QVariant::Double || val.type() == QVariant::Int){
        double dval = devicevalue.value<double>();
        double dval2 = val.value<double>();
        if(dval > dval2){
            devicevalue = val;
            return true;
        }
        return false;
    }else if(val.type() == QVariant::Bool){
        bool sta = val.value<bool>();
        if(!sta){
             devicevalue = val;
             return true;
        }
        return false;
    }
}

bool Filters::maximumValueConversion(QVariant val){
    if(val.type() == QVariant::Double || val.type() == QVariant::Int){
        double dval = devicevalue.value<double>();
        double dval2 = val.value<double>();
        if(dval < dval2){
            devicevalue = val;
            return true;
        }
        return false;
    }else if(val.type() == QVariant::Bool){
        bool sta = val.value<bool>();
        if(sta){
             devicevalue = val;
             return true;
        }
        return false;
    }
}

bool Filters::exactValueConversion(QVariant val){
    if(val != devicevalue){
        devicevalue = val;
    }
    return true;
}
