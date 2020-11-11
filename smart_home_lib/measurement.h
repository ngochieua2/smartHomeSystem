#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QMetaType>
#include <QVariant>

/**
 * @brief The Measurement class
 *
 * TODO: This is just a placeholder so that the MessageFactory can
 * reference it. You need to implement it properly.
 */
class Measurement
{
public:
  Measurement();
   QString deviceName();
   int measurementType();
   long timestamp();
   QVariant value();
   QString unitOfMEasure();
   bool isFiltered();//已筛选
  QVariant devicevalue;

};

// You may need this to make it compatiable with QVariant
// You may also need to use it on each instantiation of the
// template subclass.
Q_DECLARE_METATYPE(Measurement)

#endif // MEASUREMENT_H
