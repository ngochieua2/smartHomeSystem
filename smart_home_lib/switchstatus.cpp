#include "switchstatus.h"

//SwitchStatus::SwitchStatus()
//{

//}

SwitchStatus::SwitchStatus(QString deviceName, Measurement::measurementType type, QVariant value)
    :filter(deviceName,type,value)
{

}

QString SwitchStatus::switchConversion(){
    bool status = devicevalue.value<bool>();
    if(status){
        return "ON";
    }else {
        return "OFF";
    }
}
