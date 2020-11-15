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
     * @brief getID return id of a controller
     * @return 
     */
    QString getID();
    /*!
     * @brief registerDevice  records information about the specified device given its 
     * 'name', 'type', and 'URL', through create device proxy inside controller
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
     * @brief getLightSwitchProxy return a light switch proxy in list
     * @return LightSwitchProxy
     */
    LightSwitchProxy* getLightSwitchProxy();
    /*!
     * @brief getLightSwitchProxyList return a list of light switch proxy in realcontroller
     * @return QList
     */
    QList<LightSwitchProxy*> getLightSwitchProxyList();
    /*!
     * @brief getThermostatProxy return a thermostat proxy in list
     * @return ThermostatProxy
     */
    ThermostatProxy* getThermostatProxy();
    /*!
     * @brief getThermostatProxyList return a list of thermostat proxy in realcontroller
     * @return QList
     */
    QList<ThermostatProxy*> getThermostatProxyList();
    /*!
     * @brief getSprinklerSystemProxy return a Sprinkler System proxy in list
     * @return SprinklerSystemProxy
     */
    SprinklerSystemProxy* getSprinklerSystemProxy();
    /*!
     * @brief getSprinklerSystemProxyList return a list of Sprinkler System proxy in realcontroller
     * @return QList
     */
    QList<SprinklerSystemProxy*> getSprinklerSystemProxyList();
    /*!
     * @brief receiveDeviceInfo handle device info when recieved from controller proxy
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
     * @brief getUpdateMeasurement returns reported measurement from device
     * it can be empty if nothing changes in device
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
