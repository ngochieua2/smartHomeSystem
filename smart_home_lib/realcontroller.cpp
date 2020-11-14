#include "realcontroller.h"

RealController::RealController()
{
}

RealController::RealController(QString id, QUrl Url)
{
    _controller_id = id;
    _controller_Url = Url;
}

RealController::~RealController()
{
    for(int i = 0 ; i <_lightSwitchProxyList.size(); ++i){
        delete _lightSwitchProxyList.at(i);
    }

}

QString RealController::getID()
{
    return _controller_id;
}

void RealController::registerDevice(QString name, QString type, QUrl URL)
{
    if(type == "lightSwitch"){
        _lightSwitchProxyList.append(new LightSwitchProxy(name, URL));
    }
    else {

    }
}

QString RealController::registerDevice()
{
    QString data{};
    if(_deviceInfoList.isEmpty()){
        data = "There is no register devices\n"
                "Please come back to main Menu and register new device\n";
    }
    else {
        for(int i = 0; i <_deviceInfoList.size(); i++ ){
            data +=  QString::number(i+1) + "." + _deviceInfoList.at(i)->showDeviceInfo();
        }
    }
    _deviceInfoList.clear();
    return data;
}

LightSwitchProxy *RealController::getLightSwitchProxy()
{
    return _lightSwitchProxyList.last();
}

QList<LightSwitchProxy *> RealController::getLightSwitchProxyList()
{
    return _lightSwitchProxyList;
}

void RealController::receiveDeviceInfo(DeviceInfo *deviceInfo)
{
    _deviceInfoList.append(deviceInfo);
}

QList<DeviceInfo *> RealController::getDeviceInfoList()
{
    return _deviceInfoList;
}
void RealController::report(QList<Measurement *> measurementList){
    _measurementList = measurementList;
}




