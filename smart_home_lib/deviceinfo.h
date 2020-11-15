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

    /*!
     * @brief updateTime is usd to record time to current time
     * When deviceInfor is taken
     */
    void updateTime();
    /*!
     * @brief showDeviceInfo display device info
     * @return device info
     */
    QString showDeviceInfo();
    /*!
     * @brief getDeviceName return name of device
     * @return device name
     */
    QString getDeviceName();
    /*!
     * @brief getDeviceType return type of a device
     * @return device type
     */
    QString getDeviceType();

private:
  QString _deviceName{};
  QString _deviceType{};
  QUrl _Url{};
  QDateTime _time{};

};

// You may need this to make it compatiable with QVariant
Q_DECLARE_METATYPE(DeviceInfo)

#endif // DEVICEINFO_H
