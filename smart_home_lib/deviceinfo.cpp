#include "deviceinfo.h"

DeviceInfo::DeviceInfo()
{

}

DeviceInfo::DeviceInfo(QString dName, QString dType, QUrl dUrl)
    :_deviceName{dName}, _deviceType{dType}, _Url{dUrl}
{}

DeviceInfo::~DeviceInfo()
{
    _deviceName = "";
    _deviceType = "";
    _Url = "";
}

QString DeviceInfo::showDeviceInfo()
{
    QString info = "Device name: " + _deviceName + "\n"
                   "Device type: " + _deviceType + "\n"
                   "Url: " + _Url.toEncoded() + "\n";

    if (_time.isNull()){
        info += "\nLast seen: This is the first seen";
    }
    else {
        info += "\nLast seen: " + _time.toString("H:m MMM dd yyyy");
    }

    return info;
}
