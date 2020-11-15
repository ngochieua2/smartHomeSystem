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
     * @brief createControllerProxy create the controller proxy of the light switch
     */
    void createControllerProxy();
    /*!
     * @brief getControllerProxy return the the controller proxy of the light switch
     * @return ControllerProxy
     */
    ControllerProxy* getControllerProxy();
    /*!
     * @brief getDeviceInfo 
     */
    void getDeviceInfo() override;
    /*!
     * @brief currentState return two Measurements, one indicating the 'ON'/'OFF' 
     * status (boolean true/false, respectively), and one indicating the 'brightness level'
     * @return QList
     */
    QList <Measurement*> currentState();
    
    void getMeasurement() override;
    /*!
     * @brief isSameValue check if the value of measurement has been changed 
     * @return 
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
