#include "smarthomecontroller.h"

SmartHomeController::SmartHomeController()
{
    m_deviceInfoList.clear();
}

SmartHomeController::SmartHomeController(QString id, QString url) : m_id(id),m_url(url)
{
    m_deviceInfoList.clear();
    QStringList tempList = m_url.split(":");
    if(tempList.length() == 2)
    {
        m_ip = tempList.at(0);
        m_port = tempList.at(1);
    }
}

SmartHomeController::~SmartHomeController()
{

}

void SmartHomeController::registerDevice(QString name, QString type, QUrl URL)
{

    DeviceInfo *deviceInfo = new DeviceInfo(name,type,URL);
    m_deviceInfoList.append(deviceInfo);

}

QString SmartHomeController::registerdDevices()
{

    if(m_deviceInfoList.count() <= 0)
    {
        qDebug();
        return "";
    }

    QString allInfo;

    foreach(DeviceInfo *deviceInfo,m_deviceInfoList)
    {

        QString info = deviceInfo->showDeviceInfo() + "\n";
        allInfo += info;
    }

    return allInfo;
}
bool SmartHomeController::unregisterDevice(QString name)
{
    if(name == "")
    {
        return false;
    }
    int index = 0;
    foreach(DeviceInfo *deviceInfo,m_deviceInfoList)
    {
        if(name == deviceInfo->getDeviceName())
        {
            m_deviceInfoList.removeAt(index);
            return true;
        }
        index++;
    }
    return false;
}

QStringList SmartHomeController::currentState(QString name, QString type)
{
    QStringList stateList;
    if(name == "" && type == "")
    {
        foreach(DeviceInfo *deviceInfo,m_deviceInfoList)
        {
            QString info = deviceInfo->currentState();
            stateList.append(info);
        }
    }
    else if(name == "" && type != "")
    {
        foreach(DeviceInfo *deviceInfo,m_deviceInfoList)
        {
            if(deviceInfo->getDeviceType() == type)
            {
                QString info = deviceInfo->currentState();
                stateList.append(info);
            }
        }
    }
    else if(name != "" && type == "")
    {
        foreach(DeviceInfo *deviceInfo,m_deviceInfoList)
        {
            if(deviceInfo->getDeviceName() == name)
            {
                QString info = deviceInfo->currentState();
                stateList.append(info);
            }
            else
            {
                QString info = "none";
                stateList.append(info);
            }
        }
    }
    else if(name != "" && type != "")
    {
        foreach(DeviceInfo *deviceInfo,m_deviceInfoList)
        {
            if(deviceInfo->getDeviceName() == name && deviceInfo->getDeviceType() == type)
            {

                QString info = deviceInfo->currentState();
                stateList.append(info);
            }
            else
            {
                stateList.clear();
            }
        }
    }

    return stateList;
}
