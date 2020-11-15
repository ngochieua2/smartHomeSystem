#ifndef CONTROLLERPROXY_H
#define CONTROLLERPROXY_H

#include <smarthomecontroller.h>
#include <realcontroller.h>

class RealController;

class ControllerProxy : public SmartHomeController
{
public:
    ControllerProxy();
    virtual ~ControllerProxy();

    /*!
     * @brief passController pass the Real Controller to controller proxy
     * @param controller
     */
    void passController(RealController* controller);

    /*!
     * @brief receiveDeviceInfo calls real controller to handle device information when it is recieved
     * @param deviceInfo
     */
    void receiveDeviceInfo(DeviceInfo *deviceInfo) override;
    /*!
     * @brief report returns new measurement when state changes occur or new measurement values are produced
     * @param measurementList
     */
    void report(QList<Measurement *> measurementList) override;

private:
    RealController* _realController{nullptr};
};

#endif // CONTROLLERPROXY_H
