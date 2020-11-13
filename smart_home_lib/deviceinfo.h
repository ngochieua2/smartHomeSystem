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

private:
  QString _deviceName{};
  QString _deviceType{};
  QUrl _Url{};
  QDateTime _time{};

};

// You may need this to make it compatiable with QVariant
Q_DECLARE_METATYPE(DeviceInfo)

#endif // DEVICEINFO_H
