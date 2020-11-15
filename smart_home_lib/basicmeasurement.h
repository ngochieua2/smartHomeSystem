#ifndef BASICMEASUREMENT_H
#define BASICMEASUREMENT_H

#include <measurement.h>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QVariant>

template<class T>
class BasicMeasurement : public Measurement
{
public:
    BasicMeasurement();
    ~BasicMeasurement();

private:
   T dataValue;

};

Q_DECLARE_METATYPE(BasicMeasurement<bool>)
Q_DECLARE_METATYPE(BasicMeasurement<int>)
Q_DECLARE_METATYPE(BasicMeasurement<double>)


#endif // BASICMEASUREMENT_H
