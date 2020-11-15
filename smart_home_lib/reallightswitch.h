#ifndef REALLIGHTSWITCH_H
#define REALLIGHTSWITCH_H

#include <lightswitch.h>
#include <controllerproxy.h>

class ControllerProxy;

class RealLightSwitch : public LightSwitch
{
public:
    RealLightSwitch();
    RealLightSwitch(QString id, QUrl URL);
    virtual ~RealLightSwitch();
    /*!
     * @brief turnOn change the state to 'ON'
     * if state change, it will report back to controller
     */
    void turnOn() override;
    /*!
     * @brief turnOff change the state to 'OFF'
     * if state change, it will report back to controller
     */
    void turnOff() override;
    /*!
     * @brief dim reduce the 'brightness level' by 20 points if currently greater than 20, otherwise 
     * will do nothing (cannot be reduced to zero brightness).
     * if state change, it will report back to controller
     */
    void dim() override;
    /*!
     * @brief brighten increase the 'brightness level' by 20 points if currently less than 100, 
     * otherwise will do nothing (cannot go above 100 percent)
     * if state change, it will report back to controller
     */
    void brighten() override;
    /*!
     * @brief createControllerProxy create the controller proxy in light switch
     */
    void createControllerProxy();
    /*!
     * @brief getControllerProxy return the the controller proxy in light switch
     * @return ControllerProxy
     */
    ControllerProxy* getControllerProxy();
    /*!
     * @brief getDeviceInfo is usd to send its info to controller
     */
    void getDeviceInfo() override;
    /*!
     * @brief currentState return two Measurements, one indicating the 'ON'/'OFF' 
     * status (boolean true/false, respectively), and one indicating the 'brightness level'
     * @return QList
     */
    QList <Measurement*> currentState();
    /*!
     * @brief getMeasurement send device measurement to controller
     * it can be empty if nothing change
     *
     */
    void getMeasurement() override;
    /*!
     * @brief isSameValue check if the value of measurement has been changed
     * do command from controller
     * @return bool
     */
    bool isSameValue();

// functions for testing
    bool getState();
    int getBrightness();
private:
    bool OnOffState{};
    int brightnessLevel{};

    ControllerProxy* _controllerProxy{};

    DeviceInfo* _deviceInfo{nullptr};

    Measurement* _measurement{nullptr};
    QList <Measurement*> _mesurementList{};

    QList <Measurement*> _measurementRecord{};

};

#endif // REALLIGHTSWITCH_H
