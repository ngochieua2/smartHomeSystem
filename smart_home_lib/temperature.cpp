#include "temperature.h"

Temperature::Temperature()
{

}
QString Temperature::temperatureConversion(double val,QString type){
    double cc = val;
    if(type == "F"){
        cc = (val - 32) * 5 / 9;
    }
    if(cc <= 0){
        return "freezing";
    }else if(cc <= 15){
        return "cold";
    }else if(cc < 28){
        return "'balmy";
    }else if(cc < 40){
        return "hot";
    }else{
        return "scorching";
    }
}
