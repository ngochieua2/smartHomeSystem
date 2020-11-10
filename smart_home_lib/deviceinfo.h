#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QMetaType>
#include <QString>
#include <QUrl>
#include <QDateTime>

/**
 * @brief The DeviceInfo class/struct
 *
 * TODO: This is just a placeholder so that the MessageFactory can
 * reference it. You need to implement it properly.
 */
class DeviceInfo
{
public:
    DeviceInfo();
    DeviceInfo(QString dName, QString dType, QUrl dUrl);
    ~DeviceInfo();

    QString showDeviceInfo();


  protected:
    QString _deviceName{};
    QString _deviceType{};
    QUrl _Url{};
    QDateTime _time{};
};

// You may need this to make it compatiable with QVariant
Q_DECLARE_METATYPE(DeviceInfo)

#endif // DEVICEINFO_H
