#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QMetaType>
#include <QString>
#include <QUrl>
#include <QDateTime>

class DeviceInfo
{
public:
    DeviceInfo();
    DeviceInfo(QString dName, QString dType, QUrl dUrl);
    ~DeviceInfo();
    void updateTime();
    QString showDeviceInfo();

    QString getDeviceName()
    {
        return _deviceName;
    }
    QString getDeviceType()
    {
        return _deviceType;
    }

    QString currentState()
    {
        return m_currentState;
    }

private:
  QString _deviceName{};
  QString _deviceType{};
  QUrl _Url{};
  QDateTime _time{};

  QString m_currentState;

};

// You may need this to make it compatiable with QVariant
Q_DECLARE_METATYPE(DeviceInfo)

#endif // DEVICEINFO_H
