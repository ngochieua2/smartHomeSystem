#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QMetaType>
#include <QString>

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
  virtual void MenuInterface();
  virtual void currentState();
  void turnOn();
  void turnOff();
  QString name;
  QString id;
  int Port;
  QString IPAddress;

};

// You may need this to make it compatiable with QVariant
Q_DECLARE_METATYPE(DeviceInfo)

#endif // DEVICEINFO_H
