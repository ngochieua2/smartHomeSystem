#ifndef SMARTHOMEDEVICES_H
#define SMARTHOMEDEVICES_H
#include "mainmenu.h"
#include "measurement.h"
//#include "controllerproxy.h"
#include <QString>
#include <QUrl>

class ControllerProxy;
class SmartHomeDevices
{
public:
    SmartHomeDevices();
    ~SmartHomeDevices();
    /**
     * @brief currentState will return current state, value depends on the type of device
     */
    //virtual Measurement currentState();
    /**
     * @brief setControllerProxy set controller proxy for a device
     * @param controllerProxy
     */
    virtual void setControllerProxy(ControllerProxy* controllerProxy);
    QString getId();
protected:
    QString _Device_id{};
    QString _devideType{};
    QUrl _Url{};
    ControllerProxy* _controllerProxy{};
};

#endif // SMARTHOMEDEVICES_H
