#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QVariant>
#include <iostream>
#include <cmath>
/*!
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
  QVariant devicevalue;
  /*!
   * @brief deviceName return device name
   * @return name
   */
  virtual QString deviceName();
  /*!
   * @brief measurementType is emun class include the collection of all measurement
   */
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
  
  /*!
   * @brief timestamp returns the date/time (refer to QDateTime) at which the measurement was 'taken'
   * @return date/time
   */
  virtual QDateTime timestamp();
  /*!
   * @brief value returns a QVariant containing the (possibly filtered) value of the measurement: 
   * the use of QVariant hides the underlying data type allowing a consistent interface to be 
   * presented to clients
   * @return QVariant
   */
  virtual QVariant value();
  /*!
   * @brief unitOfMeasure returns a string representing the Unit of Measure (UoM) of the value
   * @return QString
   */
  QString unitOfMeasure();
  /*!
   * @brief isFiltered returns true/false to indicate whether this is a filtered measurement or 
   * not, respectively
   * @return boolean
   */
  bool isFiltered();
  /*!
   * @brief rawMeasurementreturns base measurement object without any filters; if the measurement 
   * is a base measurement, should return itself
   * @return Measurement
   */
  Measurement *rawMeasurement();
  /*!
   * @brief displayMeasurement display measurement info to screen
   * @return QString
   */
  QString displayMeasurement();
  /*!
   * @brief getTakenTime return taken time a string
   * @return QString
   */
  QString getTakenTime();
  /*!
   * @brief getType return the type of a measurement
   * @return a measurementType
   */
  Measurement::measurementType getType();

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
