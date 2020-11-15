#ifndef REALCONTROLLER_H
#define REALCONTROLLER_H

#include <smarthomecontroller.h>
#include <lightswitchproxy.h>
#include <thermostatproxy.h>
#include <sprinklersystemproxy.h>

class LightSwitchProxy;
class ThermostatProxy;
class SprinklerSystemProxy;

class RealController : SmartHomeController
{
public:
    RealController();
    RealController(QString id, QUrl Url);
    virtual ~RealController();
    /*!
     * @brief getID return id of a device
     * @return 
     */
    QString getID();
    /*!
     * @brief registerDevice  records information about the specified device given its 
     * 'name', 'type', and 'URL', registered devices can be queried and be sent commands
     * @param name
     * @param type
     * @param URL
     */
    void registerDevice(QString name, QString type, QUrl URL);
    /*!
     * @brief registerDevice returns basic information about all of the currently registered 
     * devices, including: name, type, URL, and last seen time (i.e., the time at which it 
     * last received information from the device either as a result of an automatic report 
     * or an explicit query)
     * @return QString
     */
    QString registerDevice();
    /*!
     * @brief unregisterDevice removes the specified device from the list of registered devices
     * @param name
     */
    void unregisterDevice(QString name);
    /*!
     * @brief getLightSwitchProxy return a light switch proxy 
     * @return LightSwitchProxy
     */
    LightSwitchProxy* getLightSwitchProxy();
    /*!
     * @brief getLightSwitchProxyList return a list of light switch proxy
     * @return QList
     */
    QList<LightSwitchProxy*> getLightSwitchProxyList();
    /*!
     * @brief getThermostatProxy return a thermostat proxy
     * @return ThermostatProxy
     */
    ThermostatProxy* getThermostatProxy();
    /*!
     * @brief getThermostatProxyList return a list of thermostat proxy
     * @return QList
     */
    QList<ThermostatProxy*> getThermostatProxyList();
    /*!
     * @brief getSprinklerSystemProxy return a Sprinkler System proxy
     * @return SprinklerSystemProxy
     */
    SprinklerSystemProxy* getSprinklerSystemProxy();
    /*!
     * @brief getSprinklerSystemProxyList return a list of Sprinkler System proxy
     * @return QList
     */
    QList<SprinklerSystemProxy*> getSprinklerSystemProxyList();
    /*!
     * @brief receiveDeviceInfo handle device info when recieved
     * @param deviceInfo
     */
    void receiveDeviceInfo(DeviceInfo *deviceInfo) override;
    /*!
     * @brief report records 1 or more Measurements at the controller
     * @param measurementList
     */
    void report(QList<Measurement *> measurementList) override;
    /*!
     * @brief currentState returns a summary of the current state of the registered 
     * devices (that is the same Measurements that would be returned by calling the
     * currentState on each device but including both the raw and filtered values); 
     * the parameters 'name' and  'type' act as filters
     * @param name
     * @param Type
     * @return QString
     */
    QString currentState(QString name, QString Type);
    /*!
     * @brief getUpdateMeasurement returns updated measurement
     * @return QString
     */
    QString getUpdateMeasurement();

private:
    QList <LightSwitchProxy*> _lightSwitchProxyList{};
    QList <ThermostatProxy*> _thermostatProxyList{};
    QList <SprinklerSystemProxy*> _sprinklerSystemProxyList{};

    QList<DeviceInfo*> _deviceInfoList{};

    QList<Measurement*> _measurementList{};

};

#endif // REALCONTROLLER_H
