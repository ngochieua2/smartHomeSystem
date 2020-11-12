#ifndef SMARTHOMECONTROLLER_H
#define SMARTHOMECONTROLLER_H
#include <QString>
#include <QUrl>
#include <QList>
#include "thermostatproxy.h"
#include "sprinklersystemproxy.h"
#include "measurement.h"
#include <deviceinfo.h>

class LightSwitchProxy;
class SmartHomeController
{
public:
    SmartHomeController();
    SmartHomeController(QString id, QUrl url);    
    ~SmartHomeController();

    /**
     * @brief registerDevice records information about the specified device given its 'name', 'type', and 'URL', 
     * registered devices can be queried and be sent commands
     * @param name
     * @param type
     * @param url
     */
    virtual void registerDevice(QString id,QString type,QUrl url) = 0;
    /**
     * @brief registeredDevices which returns basic information about all of the currently registered devices, 
     * including: name, type, URL, and last seen time (i.e., the time at which it last received information 
     * from the device either as a result of an automatic report or an explicit query)
     */
    virtual void registeredDevices() = 0;

    virtual void unregisterDevice(QString id) = 0;

    //void report(measurement);

    // currentState();

    //void addfilter(QString deviceName, measurementType, filterType, configuration);

    //void clearFilter(QString deviceName, measurementType);

    virtual QString configController(QString id, QUrl URL) = 0;


protected:
    std::vector<LightSwitchProxy*> _lightSwitchProxy{};
    std::vector<ThermostatProxy*> _thermostatProxy{};
    std::vector<SprinklerSystemProxy*> _sprinklerSystemProxy{};
    
    QString _controller_id{};
    QUrl _controller_Url{};
    //measurement
    DeviceInfo* _deviceInfoPointer{nullptr};
};

#endif // SMARTHOMECONTROLLER_H
