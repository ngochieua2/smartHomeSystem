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
     * @brief getID
     * @return 
     */
    QString getID();
    /*!
     * @brief turnOn change the state to 'ON' if it is 'OFF', otherwise will do nothing
     */
    void turnOn() override;
    /*!
     * @brief turnOff change the state to 'OFF' if it is currently 'ON', otherwise will do nothing
     */
    void turnOff() override;
    /*!
     * @brief dim reduce the 'brightness level' by 20 points if currently greater than 20, otherwise 
     * will do nothing (cannot be reduced to zero brightness)
     */
    void dim() override;
    /*!
     * @brief brighten increase the 'brightness level' by 20 points if currently less than 100, 
     * otherwise will do nothing (cannot go above 100 percent)
     */
    void brighten() override;
    /*!
     * @brief passRealLightSwitch set up the real light switch to the proxy
     * @param realLightSwitch
     */
    void passRealLightSwitch(RealLightSwitch* realLightSwitch);
    /*!
     * @brief getDeviceInfo handle information of device to report to controller
     */
    void getDeviceInfo() override;

    void getMeasurement() override;

private:
    RealLightSwitch* _realLightSwitch{nullptr};
};

#endif // LIGHTSWITCHPROXY_H
