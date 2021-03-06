#include "filter.h"

filter::filter()
{

}

bool filter::minimumValueConversion(QVariant val){
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

bool filter::maximumValueConversion(QVariant val){
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

bool filter::exactValueConversion(QVariant val){
    if(val != devicevalue){
        devicevalue = val;
    }
    return true;
}
