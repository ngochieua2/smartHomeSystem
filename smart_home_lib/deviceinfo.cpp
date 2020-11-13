#include "deviceinfo.h"

DeviceInfo::DeviceInfo()
{
}

DeviceInfo::DeviceInfo(QString dName, QString dType, QUrl dUrl)
    :_deviceName{dName}, _deviceType{dType}, _Url{dUrl}
{
}

DeviceInfo::~DeviceInfo()
{
    _deviceName = "";
    _deviceType = "";
    _Url = "";
    _time.setTime(QTime());
}

void DeviceInfo::updateTime()
{
    _time = QDateTime::currentDateTime();
}

QString DeviceInfo::showDeviceInfo()
{
    QString info = "Device name: " + _deviceName + "\n"
                   "Device type: " + _deviceType + "\n"
                   "Url: " + _Url.toEncoded() + "\n";

    if (_time.isNull()){
        info += "Last seen: This is the first seen\n\n";
    }
    else {
        info += "Last seen: " + _time.toString("H:m:s MMM dd yyyy") + "\n\n";
    }

    return info;
}
