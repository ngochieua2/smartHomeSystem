#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QVariant>
#include <iostream>
#include <cmath>
/**
 * @brief The Measurement class
 *
 * TODO: This is just a placeholder so that the MessageFactory can
 * reference it. You need to implement it properly.
 */
class Measurement
{
public:
  enum class measurementType;
  Measurement();
  Measurement(QString deviceName, measurementType type,QVariant value);
  virtual ~Measurement();

  virtual QString deviceName();

  enum class measurementType:int{
      lightSwitchOnOff = 1,
      brightnessLevel,
      temperature,
      temperatureSetpoint,
      thermostatState,
      sprinklerState,
      scheduledTime,
      scheduledDuration,
      waterUsage,
      totalWaterUsage
  };

  virtual QDateTime timestamp();

  virtual QVariant value();

  QString unitOfMeasure();

  bool isFiltered();

  Measurement *rawMeasurement();

  QString displayMeasurement();

  QString getTakenTime();

protected:
  Measurement *_rawMeasurement{nullptr};
  QString _deviceName{};
  QVariant _value{};
  QDateTime _timestamp{};
  measurementType _type{};


};

// You may need this to make it compatiable with QVariant
// You may also need to use it on each instantiation of the
// template subclass.
Q_DECLARE_METATYPE(Measurement)

#endif // MEASUREMENT_H
