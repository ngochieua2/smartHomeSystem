#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QString>
#include <vector>
#include "lightswitchproxy.h"
#include "thermostatproxy.h"
#include "sprinklersystemproxy.h"
#include "lightswitchfactory.h"
#include "thermostatfactory.h"
#include "sprinklersystemfactory.h"
#include "measurement.h"

class Controller
{
public:
    Controller();
    ~Controller();
    Controller(QString id, QUrl url);
    /**
     * @brief registerDevice records information about the specified device given its 'name', 'type', and 'URL', 
     * registered devices can be queried and be sent commands
     * @param name
     * @param type
     * @param url
     */
    virtual void registerDevice(QString name,QString type,QUrl url) = 0;
    /**
     * @brief registeredDevices which returns basic information about all of the currently registered devices, 
     * including: name, type, URL, and last seen time (i.e., the time at which it last received information 
     * from the device either as a result of an automatic report or an explicit query)
     */
    virtual void registeredDevices() = 0;
protected:
    std::vector<LightSwitchProxy*> _lightSwitchProxy;
    std::vector<ThermostatProxy*> _thermostatProxy;
    std::vector<SprinklerSystemProxy*> _sprinklerSystemProxy;
    LightSwitchFactory _lightswitchFactory;
    ThermostatFactory _thermostatFactory;
    SprinklerSystemFactory _sprinklerFactory;
    QString _id;
    QUrl _url;
};

#endif // CONTROLLER_H
