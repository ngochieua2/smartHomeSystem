#ifndef LIGHTSWITCHPROXY_H
#define LIGHTSWITCHPROXY_H

#include <lightswitch.h>
#include <reallightswitch.h>

class RealLightSwitch;

class LightSwitchProxy : public LightSwitch
{
public:
    LightSwitchProxy();
    LightSwitchProxy(QString id, QUrl URL);
    virtual ~LightSwitchProxy();
    /*!
     * @brief getID returns id (name) of device
     * @return id of device
     */
    QString getID();
    /*!
     * @brief turnOn requires real device to change the state to 'ON',
     */
    void turnOn() override;
    /*!
     * @brief turnOff requires real device to change the state to 'OFF'
     */
    void turnOff() override;
    /*!
     * @brief dim requires real device to reduce the 'brightness level' by 20 points
     * if currently greater than 20, otherwise
     * will do nothing (cannot be reduced to zero brightness)
     */
    void dim() override;
    /*!
     * @brief brighten requires real device to increase the 'brightness level' by 20 points
     * if currently less than 100,
     * otherwise will do nothing (cannot go above 100 percent)
     */
    void brighten() override;
    /*!
     * @brief passRealLightSwitch set up the real light switch to the proxy
     * @param realLightSwitch
     */
    void passRealLightSwitch(RealLightSwitch* realLightSwitch);
    /*!
     * @brief getDeviceInfo requires real device to send its info back to controller
     */
    void getDeviceInfo() override;
    /*!
     * @brief getDeviceInfo requires real device to send its measurement
     * or current state back to controller
     */
    void getMeasurement() override;

private:
    RealLightSwitch* _realLightSwitch{nullptr};
};

#endif // LIGHTSWITCHPROXY_H
