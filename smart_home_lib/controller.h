#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QString>
#include <vector>
#include "lightswitch.h"
#include "lightswitchproxy.h"
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
    void registerDevice(QString name,QString type,QUrl url);
    /**
     * @brief registeredDevices which returns basic information about all of the currently registered devices, 
     * including: name, type, URL, and last seen time (i.e., the time at which it last received information 
     * from the device either as a result of an automatic report or an explicit query)
     */
    void registeredDevices();
};

#endif // CONTROLLER_H
