#ifndef SMARTHOMECONTROLLER_H
#define SMARTHOMECONTROLLER_H

#include <QString>
#include <QUrl>
#include <QList>
#include <QDebug>
#include "deviceinfo.h"
#include <measurement.h>
/*!
 * @brief SmartHomeController is abtract class, so some fuctions on this class
 * will not be implement
 */
class SmartHomeController
{
public:
    SmartHomeController();
    SmartHomeController(QString id,QString url);
    ~SmartHomeController();
    /*!
     * @brief registerDevice  records information about the specified device given its 
     * 'name', 'type', and 'URL', registered devices can be queried and be sent commands
     * @param name
     * @param type
     * @param URL
     */
    void registerDevice(QString name,QString type,QUrl URL);
    /*!
     * @brief registerDevice returns basic information about all of the currently registered 
     * devices, including: name, type, URL, and last seen time (i.e., the time at which it 
     * last received information from the device either as a result of an automatic report 
     * or an explicit query)
     * @return QString
     */
    QString registerdDevices();
    /*!
     * @brief unregisterDevice removes the specified device from the list of registered devices
     * @param name
     */
    bool unregisterDevice(QString name);
    /*!
     * @brief currentState returns a summary of the current state of the registered 
     * devices (that is the same Measurements that would be returned by calling the
     * currentState on each device but including both the raw and filtered values); 
     * the parameters 'name' and  'type' act as filters
     * @param name
     * @param Type
     * @return QString
     */
    QStringList currentState(QString name = "", QString type = "");
    /*!
     * @brief addFilter adds configuration for a measurement filter to the device with the specified 
     * 'name' for the particular 'measurement type' (e.g., temperature, light switch state, etc.), 
     * and using the given configuration parameters, which can be provided as a set of key-value 
     * pairs to be processed based on the specified 'filter type'.
     * @param deviceName
     * @param measurementType
     * @param filterType
     * @param configuration
     */
    void addFilter(QString deviceName,int measurementType,int filterType,QString configuration);
    /*!
     * @brief clearFilter removes all filters from the measurements of the specified type from the 
     * specified registered device; if a measurement type is not specified all filters for all 
     * measurement types will be removed
     * @param deviceName
     * @param measurementType
     */
    void clearFilter(QString deviceName,int measurementType);
    /*!
     * @brief receiveDeviceInfo handle device information when it is recieved
     * @param deviceInfo
     */
    virtual void receiveDeviceInfo(DeviceInfo *deviceInfo) = 0;
    /*!
     * @brief report reports to controller when state changes occur or new measurement values are produced
     * @param measurementList
     */
    virtual void report(QList<Measurement *> measurementList) = 0;

private:

    QString m_id{};
    QString m_name{};
    QString m_url{};
    QString m_ip{};
    QString m_port{};

    QList<DeviceInfo*> m_deviceInfoList;

protected:

    QString _controller_id{};
    QUrl _controller_Url{};

};


#endif // SMARTHOMECONTROLLER_H
