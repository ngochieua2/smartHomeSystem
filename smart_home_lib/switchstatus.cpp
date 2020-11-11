#include "switchstatus.h"

SwitchStatus::SwitchStatus()
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
